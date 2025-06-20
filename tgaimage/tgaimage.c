#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct {
	uint8_t id_length;
	uint8_t color_map_type;
	uint8_t image_type;

	// color map specification
	uint16_t first_entry_index;
	uint16_t color_map_length;
	uint8_t color_map_entry_size;

	// image specification
	uint16_t x_origin;
	uint16_t y_origin;
	uint16_t width;
	uint16_t height;
	uint8_t pixel_depth;
	uint8_t image_descriptor;
} TGAHeader;

// implementation defined, here RGB thus 24 bit (1 byte per pixel)
typedef struct {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
#ifdef SUPPORT_ALPHA
	uint8_t alpha;
#endif
} TGAPixel;

typedef struct {
	TGAHeader tga_header;
	uint8_t *image_id;
	uint8_t *color_map_data;
	TGAPixel *image_data;
} TGAImage;

static TGAHeader tga_make_header(uint16_t width,uint16_t height)
{
	TGAHeader header = {0};
	header.id_length = 0; // no image id
	header.color_map_type = 0; // no color map
	header.image_type = 2; // uncompressed true color image

	// color map specification
	header.first_entry_index = 0;
	header.color_map_length = 0;
	header.color_map_entry_size = 0;

	// image specification
	header.x_origin = 0;
	header.y_origin = 0;
	header.width = width;
	header.height = height;
	header.pixel_depth = 24;
#ifdef SUPPORT_ALPHA
	header.image_descriptor = 0x08;
#endif
	header.image_descriptor = 0x00;

	return header;
}

void tga_write(TGAImage image, FILE *file) {
	TGAHeader header = image.tga_header;
	fputc(header.id_length, file);
	fputc(header.color_map_type, file);
	fputc(header.image_type, file);

	fputc(header.first_entry_index & 0x00FF, file), fputc(header.first_entry_index & 0xFF00, file);
	fputc(header.color_map_length & 0x00FF, file), fputc(header.color_map_length & 0xFF00, file);
	fputc(header.color_map_entry_size, file);

	fputc(header.x_origin & 0x00FF, file), fputc(header.x_origin & 0xFF00, file);
	fputc(header.y_origin & 0x00FF, file), fputc(header.y_origin & 0xFF00, file);
	fputc(header.width & 0x00FF, file), fputc(header.width & 0xFF00, file);
	fputc(header.height & 0x00FF, file), fputc(header.height & 0xFF00, file);
	fputc(header.pixel_depth, file);
	fputc(header.image_descriptor, file);

	for (size_t i = 0; i < header.id_length; i++)
		fputc(*image.image_id++, file);

	for (size_t i = 0; i < header.color_map_length; i++)
		fputc(*image.color_map_data++, file);

	for (size_t i = 0; i < header.width * header.height; i++) {
		fputc(image.image_data->blue, file);
		fputc(image.image_data->green, file);
		fputc(image.image_data->red, file);
#ifdef SUPPORT_ALPHA
		fputc(image_data->alpha, file);
#endif
		image.image_data++;
	}
}

int main()
{
	TGAHeader header = tga_make_header(400, 400);
	TGAImage image = {0};
	image.tga_header = header;

	TGAPixel *image_data = malloc(sizeof(*image_data) * header.width * header.height);
	for (size_t i = 0; i < header.width * header.height; i++) {
		image_data[i].red = 0;
		image_data[i].green = 255;
		image_data[i].blue = 0;
	}
	image.image_data = image_data;

	FILE *image_file = fopen("testfile.tga", "w");
	tga_write(image, image_file);

	return 0;
}
