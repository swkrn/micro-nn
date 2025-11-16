#include "reader.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t read_big_endian_int(FILE *f) {
    uint8_t bytes[4];
    fread(bytes, 1, 4, f);
    return (bytes[0] << 24) |
           (bytes[1] << 16) |
           (bytes[2] << 8)  |
           (bytes[3]);
}

int read_labels(const char *filename, struct Images *images) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening file");
        return -1;
    }

    uint32_t magic = read_big_endian_int(fp);
    uint32_t num_labels = read_big_endian_int(fp);

    printf("read_labels(%s)\n", filename);
    printf("- magic: %u\n", magic);
    printf("- labels count: %u\n", num_labels);

    images->labels = malloc(num_labels * sizeof(uint8_t));
    fread(images->labels, sizeof(uint8_t), num_labels, fp);

    fclose(fp);
    return 0;
}

int read_images(const char *filename, struct Images *images) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening file");
        return -1;
    }

    uint32_t magic = read_big_endian_int(fp);
    uint32_t num_images = read_big_endian_int(fp);
    uint32_t width = read_big_endian_int(fp);
    uint32_t height = read_big_endian_int(fp);

    printf("read_images(%s)\n", filename);
    printf("- magic: %u\n", magic);
    printf("- images count: %u\n", num_images);
    printf("- width: %u\n", width);
    printf("- height: %u\n", height);

    images->n = num_images;
    images->each_width = width;
    images->each_height = height;
    images->each_size = width * height;

    images->images = malloc(num_images * sizeof(uint8_t *));

    for (uint32_t i = 0; i < num_images; i++) {
        uint8_t *image = malloc(images->each_size);
        fread(image, sizeof(uint8_t), images->each_size, fp);
        images->images[i] = image;
    }

    fclose(fp);
    return 0;
}

int reader_read_images(
    const char *images_filename,
    const char *labels_filename,
    struct Images *images
) {
    int res = read_images(images_filename, images);
    if (res != 0) {
        return res;
    }
    res = read_labels(labels_filename, images);
    if (res != 0) {
        return res;
    }
    return res;
}

void reader_show_images(struct Images *images, int begin_index, int n) {
    assert(begin_index + n <= images->n);

    while (n--) {
        printf("\n[%d] ", begin_index);
        if (images->labels) {
            printf("label: %d", images->labels[begin_index]);
        }
        uint8_t *image = images->images[begin_index];
        for (int i = 0; i < images->each_size; i++) {
            if ((i % images->each_width) == 0) {
                putchar('\n');
            }
            uint8_t pixel = image[i];
            putchar(pixel > 128 ? '#' : '.');
        }
        putchar('\n');
        ++begin_index;
    }
}

void reader_show_labels(struct Images *images, int begin_index, int n) {
    while (n--) {
        printf("[%d] %d\n", begin_index, images->labels[begin_index]);
        ++begin_index;
    }
}
