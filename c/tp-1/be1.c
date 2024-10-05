#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "font.h"

#define PI (acos(-1))

typedef struct pixel {
  unsigned char r, g, b;
} pixel;

typedef struct image {
  int width;
  int height;
  struct pixel* data;
} image;

image* empty_image(int w, int h) {
  image * img = malloc(sizeof(image));

  pixel * data = malloc(w * h * sizeof(pixel));
  for (int i = 0; i < w * h; i++) {
    data[i].r = 0;
    data[i].g = 0;
    data[i].b = 0xff;
  }

  img->data = data;
  img->width = w;
  img->height = h;

  return img;
}

/* Écrit un entier (4 octets) dans un fichier binaire */
void fwrite_int(int data, FILE* out) {
  // fputc(data, out);
  fwrite(&data, sizeof(data), 1, out);
}

/* Écrit un octet dans un fichier binaire */
void fwrite_byte(unsigned char data, FILE* out) {
  fputc(data, out);
  // fwrite(&data, 1, 1, out);
}

void write_image(char* filename, image* img){
  FILE* fd = fopen(filename, "wb");

  fwrite_byte('B', fd); // BMP magic number
  fwrite_byte('M', fd);
  fwrite_int(14 + 40 + 3 * img->width * img->height, fd); // taille du fichier (en octets)
  fwrite_int(0, fd); // application qui a créé l'image
  fwrite_int(14 + 40, fd); // taille des en-têtes

  fwrite_int(40, fd); // taill de cet en-tête
  fwrite_int(img->width, fd); // largeur de l'image
  fwrite_int(img->height, fd); // hauteur de l'image
  fwrite_int(1 + (24 << 16), fd); // plans et bits pas pixel
  fwrite_int(0, fd); // compression
  fwrite_int(0, fd); // taille de l'image (redondant, 0 fonctionne bien)
  fwrite_int(0, fd); // résolution horizontale
  fwrite_int(0, fd); // résolution verticale
  fwrite_int(0, fd); // nombre de couleurs dans la palette (inutilisé)
  fwrite_int(0, fd); // nombre de couleurs importantes (inutilisé)

  int padding = (img->width * 3) % 4;

  for (int h = 0; h < img->height; h++) {
    for (int w = 0; w < img->width; w++) {
      pixel * pixel = &img->data[h * img->width + w];

      fwrite_byte(pixel->b, fd);
      fwrite_byte(pixel->g, fd);
      fwrite_byte(pixel->r, fd);
    }

    for (int i = 0; i < padding; i++) {
      fwrite_byte(0x00, fd);
    }
    
  }

  fclose(fd);
}

/* Colore le pixel aux coordonnées (x,y) avec la couleur color. */
void draw_pixel(int x, int y, int color, image* img) {
  if (x < 0 || y < 0 || y >= img->height || x >= img->width) return;

  pixel * pixel = &img->data[y * img->width + x];
  pixel->b = color & 0xff;
  pixel->g = (color >> 8) & 0xff;
  pixel->r = (color >> 16) & 0xff;
}

/* Remplit le rectangle dont le coin en bas à gauche est (x1,y1) et le coin en
   haut à droite est (x2,y2) avec la couleur bgcolor. */
void draw_rectangle(int x1, int y1, int x2, int y2, int bgcolor, image* img) {
  for (int y = y1; y <= y2; y++) {
    for (int x = x1; x <= x2; x++) {
      draw_pixel(x, y, bgcolor, img);
    }
  }
}

int power(int base, int exp) {
  int result = 1;
  while(exp) { result *= base; exp--; }
  return result;
}

int max(int a, int b) {
  return (a < b ) ? b : a;
}

int min(int a, int b) {
  return (a < b ) ? a : b;
}

/* Remplit le disque de centre (xc,yc) et de rayon radius avec la couleur
   color. */
void draw_circle(int xc, int yc, int color, int radius, image* img) {
  if (radius <= 0) {
    draw_pixel(xc, yc, color, img);
    return;
  }

  // Source: https://stackoverflow.com/a/1201227
  for (int x = - radius; x < radius ; x++) {
    int height = (int) sqrt(radius * radius - x * x);

    for (int y = - height; y < height; y++)
      draw_pixel(x + xc, y + yc, color, img);
  }
}

/* Dessine une ligne du point (xfrom,yfrom) au point (xto,yto), de couleur color
   et d'épaisseur width. Ignorez l'épaisseur dans un premier temps. */
void draw_line(int xfrom, int yfrom, int xto, int yto, int color, int width, image* img) {
  int nbpoints = max(abs(xfrom - xto), abs(yfrom - yto));
  float dx = ((float) (xto - xfrom)) / nbpoints;
  float dy = ((float) (yto - yfrom)) / nbpoints;

  for (int i = 0; i < nbpoints; i++) {
    draw_circle(xfrom + i * dx, yfrom + i * dy, color, width, img);
  }
}

void draw_pixel_arc(int xc, int yc, float anglefrom_rad, float angleto_rad, int x, int y, int color, int width, image* img) {
  float phi = atan2(y - yc, x - xc);
  if (phi < 0) phi += 2*PI;
  if (phi > angleto_rad || phi < anglefrom_rad) return;

  draw_circle(x, y, color, width, img);
}

/* Dessine un arc de cercle de centre (xc,yc), de rayon radius, depuis l'angle
   anglefrom jusqu'à angleto, de couleur color et d'épaisseur width. Ignorez
   l'épaisseur dans un premier temps. */
void draw_arc(int xc, int yc, int color, int radius, int anglefrom, int angleto, int width, image* img){
  if (radius <= 0) {
    draw_pixel(xc, yc, color, img);
    return;
  }

  float anglefrom_rad = (float) anglefrom * PI / 180;

  float angleto_rad = (float) angleto * PI / 180;

  // Source: https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_d%27arc_de_cercle_de_Bresenham
  int x = 0;
  int y = radius;
  int m = 5 - 4 * radius;

  while (x <= y) {
    draw_pixel_arc(xc, yc, anglefrom_rad, angleto_rad, x + xc, y + yc, color, width, img);
    draw_pixel_arc(xc, yc, anglefrom_rad, angleto_rad, y + xc, x + yc, color, width, img);
    draw_pixel_arc(xc, yc, anglefrom_rad, angleto_rad, -x + xc, y + yc, color, width, img);
    draw_pixel_arc(xc, yc, anglefrom_rad, angleto_rad, -y + xc, x + yc, color, width, img);
    draw_pixel_arc(xc, yc, anglefrom_rad, angleto_rad, x + xc, -y + yc, color, width, img);
    draw_pixel_arc(xc, yc, anglefrom_rad, angleto_rad, y + xc, -x + yc, color, width, img);
    draw_pixel_arc(xc, yc, anglefrom_rad, angleto_rad, -x + xc, -y + yc, color, width, img);
    draw_pixel_arc(xc, yc, anglefrom_rad, angleto_rad, -y + xc, -x + yc, color, width, img);

    if (m > 0) {
      y -= 1;
      m -= 8*y;
    }

    x += 1;
    m += 8*x + 4;
  }
  
}

struct face_description {
  int skin_color; // la couleur du visage

  int eye_bg_color; // la couleur du fond des yeux
  int eye_fg_color; // la couleur de la pupille

  int eyebrow_color; // la couleur des sourcils
  int eyebrow_width; // l'épaisseur des sourcils

  int nose_color; // la couleur du nez
  int nose_size; // la taille du nez

  int mouth_color; // la couleur de la bouche
  int mouth_width; // l'épaisseur de la bouche

  int mask; // présence du masque (0 ou 1)
  int mask_bg_color; // la couleur du masque
  int mask_border_color; // la couleur de la bordure du masque
  int mask_link_color; // la couleur des liens du masque
};


/* Dessine un visage. Ignorez le paramètre face_description pour le moment. */
void draw_face(int x, int y, struct face_description* f, image* img){
  
  // visage
  draw_circle(x, y, f->skin_color, 40, img);

  // oeil droit
  draw_circle(x + 20, y + 10, f->eye_bg_color, 10, img);
  draw_arc   (x + 20, y + 10, 0x000000, 10, 0, 360, 1, img);
  draw_circle(x + 20, y + 5 , f->eye_fg_color, 3, img);

  // oeil gauche
  draw_circle(x - 20, y + 10, f->eye_bg_color, 10, img);
  draw_arc   (x - 20, y + 10, 0x000000, 10, 0, 360, 1, img);
  draw_circle(x - 20, y + 5 , f->eye_fg_color, 3, img);

  // sourcils
  draw_arc(x + 20, y + 10, f->eyebrow_color, 15, 45, 135, f->eyebrow_width, img);
  draw_arc(x - 20, y + 10, f->eyebrow_color, 15, 45, 135, f->eyebrow_width, img);

  // nez
  draw_circle(x, y - 5, f->nose_color, f->nose_size, img);

  // bouche
  draw_arc(x, y - 10, f->mouth_color, 20, 215, 325, f->mouth_width, img);

  if (!f->mask) return;

  // bords du masque
  draw_rectangle(x - 21, y - 26, x + 21, y - 4, f->mask_border_color, img);
  // masque
  draw_rectangle(x - 20, y - 25, x + 20, y - 5, f->mask_bg_color, img);
  // liens du masque
  draw_line(x - 20, y - 5 , x - 38, y + 5 , f->mask_link_color, 1, img);
  draw_line(x - 20, y - 25, x - 35, y - 15, f->mask_link_color, 1, img);
  draw_line(x + 20, y - 5 , x + 38, y + 5 , f->mask_link_color, 1, img);
  draw_line(x + 20, y - 25, x + 35, y - 15, f->mask_link_color, 1, img);
  
}

/* Retourne une description de visage par défaut. */
struct face_description* default_face() {
  struct face_description * face = malloc(sizeof(struct face_description));

  face->skin_color = 0xffff00;
  face->eye_bg_color = 0xffffff;
  face->eye_fg_color = 0x0000ff;

  face->eyebrow_color = 0x000000;
  face->eyebrow_width = 3;

  face->nose_color = 0x00fff0;
  face->nose_size = 7;

  face->mouth_color = 0xff0000;
  face->mouth_width = 3;

  face->mask = 1;
  face->mask_bg_color = 0xffffff;
  face->mask_border_color = 0x000000;
  face->mask_link_color = 0x000000;

  return face;
}


struct face_description* read_face(char* file) {
  struct face_description * face = default_face();
  
  FILE * fd = fopen(file, "r");
  char line[256];

  while (fgets(line, 256, fd)) {
    int i1;
    unsigned char c1, c2, c3;

    if (sscanf(line, "skin color %hhx %hhx %hhx\n", &c1, &c2, &c3) == 3) {
      face->skin_color = c3 + (c2 << 8) + (c1 << 16);
    } else if (sscanf(line, "eye color %hhx %hhx %hhx\n", &c1, &c2, &c3) == 3) {
      face->eye_fg_color = c3 + (c2 << 8) + (c1 << 16);
    } else if (sscanf(line, "eye bg color %hhx %hhx %hhx\n", &c1, &c2, &c3) == 3) {
      face->eye_bg_color = c3 + (c2 << 8) + (c1 << 16);
    } else if (sscanf(line, "eyebrow color %hhx %hhx %hhx\n", &c1, &c2, &c3) == 3) {
      face->eyebrow_color = c3 + (c2 << 8) + (c1 << 16);
    } else if (sscanf(line, "eyebrow width %d\n", &i1) == 1) {
      face->eyebrow_width = i1;
    } else if (sscanf(line, "nose color %hhx %hhx %hhx\n", &c1, &c2, &c3) == 3) {
      face->nose_color = c3 + (c2 << 8) + (c1 << 16);
    } else if (sscanf(line, "nose size %d\n", &i1) == 1) {
      face->nose_size = i1;
    } else if (sscanf(line, "mouth color %hhx %hhx %hhx\n", &c1, &c2, &c3) == 3) {
      face->mouth_color = c3 + (c2 << 8) + (c1 << 16);
    } else if (sscanf(line, "mouth width %d\n", &i1) == 1) {
      face->mouth_width = i1;
    } else if (strcmp(line, "mask yes\n") == 0) {
      face->mask = 1;
    } else if (strcmp(line, "mask no\n") == 0) {
      face->mask = 0;
    } else if (sscanf(line, "mask color %hhx %hhx %hhx\n", &c1, &c2, &c3) == 3) {
      face->mask_bg_color = c3 + (c2 << 8) + (c1 << 16);
    } else if (sscanf(line, "mask border color %hhx %hhx %hhx\n", &c1, &c2, &c3) == 3) {
      face->mask_border_color = c3 + (c2 << 8) + (c1 << 16);
    } else {
      printf("Unmatched line : %s", line);
    }
  } 

  fclose(fd);
  return face;
}

void draw_house() {
  image * house_img = empty_image(100, 100);

  draw_rectangle(55, 0, 95, 40, 0xff0000, house_img);

  draw_circle(15, 85, 0xffff00, 20, house_img);

  draw_line(55, 40, 75, 55, 0xff0000, 0, house_img);
  draw_line(75, 55, 95, 40, 0xff0000, 0, house_img);
  
  draw_arc(100, 0, 0x2c009c, 72, 90, 180, 3, house_img);
  draw_arc(100, 0, 0x000084, 75, 90, 180, 3, house_img);
  draw_arc(100, 0, 0x009cfe, 78, 90, 180, 3, house_img);
  draw_arc(100, 0, 0x00bc00, 81, 90, 180, 3, house_img);
  draw_arc(100, 0, 0xfef600, 84, 90, 180, 3, house_img);
  draw_arc(100, 0, 0xfe622c, 87, 90, 180, 3, house_img);
  draw_arc(100, 0, 0xde0000, 90, 90, 180, 3, house_img);

  write_image("house.bmp", house_img);
  
  free(house_img->data);
  free(house_img);
}

void draw_letter(unsigned char bitmap[8], int x, int y, int color, image * img) {
  for (int i = 0; i < 8; i++) {
    unsigned char line = bitmap[i];

    int j = 0;
    while (j < 8) {
      if (line & 0x01) draw_pixel(x + j, y - i, color, img);

      j++;
      line = line >> 1;
    }
  }
}

void draw_string(char * s, int x, int y, int color, image * img) {
  y += 8;
  for (int i = 0; s[i] != '\0'; i++) {
    draw_letter(font8x8_basic[(int) s[i]], x + 8*i, y, color, img);
  }
}

int main(int argc, char const *argv[]) {

  draw_house();

  if (argc != 3) return 1;

  image * face_img = empty_image(100, 100);

  struct face_description * face = read_face((char *) argv[1]);

  draw_face(50, 50, face, face_img);

  draw_string("Thomas !", 8, 0, 0xffffff, face_img);

  write_image((char *) argv[2], face_img);

  free(face_img->data);
  free(face_img);

  return 0;
}

