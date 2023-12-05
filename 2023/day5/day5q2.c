#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

struct dest_to_source {
    uint64_t dest;
    uint64_t src;
    uint64_t range;
};

uint64_t *init_seed(uint64_t *array, int *len, char *line, int pos) {
    while (line[pos] != '\n' && line[pos] != '\0') {
        while (line[pos] == ' ') {
            pos++;
        }
        uint64_t acc = 0;
        while (isdigit(line[pos])){
            acc = 10 * acc + line[pos++] - '0';
        }
        array[*len] = acc;
        *len = *len + 1;
        uint64_t *tmp = realloc(array, (*len + 1) * sizeof(uint64_t));
        if (!tmp) {
            return array;
        } if (tmp != array) {
            array = tmp;
        }
    }
    return array;
}

struct dest_to_source **init_source(struct dest_to_source **a, int *l, FILE *file) {
    char *line;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, file)) != -1) {
        if (line[0] == '\n') {
            free(line);
            return a;
        }
        int i = 0;
        struct dest_to_source *new = malloc(sizeof(struct dest_to_source));
        int w =0;
        while (line[i] != '\n' && line[i] != '\0') {
            while (line[i] == ' ') {
                i++;
            }
            uint64_t acc = 0;
            while (isdigit(line[i])){
                acc = 10 * acc + line[i++] - '0';
            }
            if (w == 0) {
                new->dest = acc;
                w++;
            } else if (w == 1) {
                new->src = acc;
                w++;
            } else if (w == 2) {
                new->range = acc;
            }

        }
        a[*l] = new;
        *l = *l + 1;
        struct dest_to_source **tmp = realloc(a, (*l + 1) * sizeof(struct dest_to_source*));
        if (!tmp) {
            return a;
        } else if (tmp != a) {
            a = tmp;
        }
    } 
    free(line);
    return a;
}

int main(void) {
    char *line;
    long unsigned int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 1;

    uint64_t *seed = malloc(sizeof(uint64_t));
    struct dest_to_source **seed_to_soil = malloc(sizeof(struct dest_to_source*));
    struct dest_to_source **soil_to_fert = malloc(sizeof(struct dest_to_source*));
    struct dest_to_source **fert_to_water = malloc(sizeof(struct dest_to_source*));
    struct dest_to_source **water_to_light = malloc(sizeof(struct dest_to_source*));
    struct dest_to_source **light_to_temp = malloc(sizeof(struct dest_to_source*));
    struct dest_to_source **temp_to_hum = malloc(sizeof(struct dest_to_source*));
    struct dest_to_source **hum_to_loc = malloc(sizeof(struct dest_to_source*));

    int len_seed = 0;
    int len_soil = 0;
    int len_fert = 0;
    int len_water = 0;
    int len_light = 0;
    int len_temp = 0;
    int len_hum = 0;
    int len_loc = 0;


    nread = getline(&line, &len, file);
    int a = 0;
    while (line[a] != ':') {
        a++;
    }
    a++;
    seed = init_seed(seed, &len_seed, line, a);

    nread = getline(&line, &len, file);
    nread = getline(&line, &len, file);
    seed_to_soil = init_source(seed_to_soil, &len_soil, file);
    
    nread = getline(&line, &len, file);
    soil_to_fert = init_source(soil_to_fert, &len_fert, file);

    nread = getline(&line, &len, file);
    fert_to_water = init_source(fert_to_water, &len_water, file);

    nread = getline(&line, &len, file);
    water_to_light = init_source(water_to_light, &len_light, file);

    nread = getline(&line, &len, file);
    light_to_temp = init_source(light_to_temp, &len_temp, file);

    nread = getline(&line, &len, file);
    temp_to_hum  = init_source(temp_to_hum, &len_hum, file);

    nread = getline(&line, &len, file);
    hum_to_loc = init_source(hum_to_loc, &len_loc, file);

    uint64_t min = 0;
    for(int i = 0; i < len_seed; i+= 2) {
        for (uint64_t k = 0; k < seed[i + 1]; k++)
        { 
            uint64_t num = seed[i] + k;
            for (int j = 0; j < len_soil; j++) {
                if (num >= seed_to_soil[j]->src && num < (seed_to_soil[j]->src + seed_to_soil[j]->range)) {
                    num = seed_to_soil[j]->dest + (num - seed_to_soil[j]->src);
                    break;
                }
            }
            for (int j = 0; j < len_fert; j++) {
                if (num >= soil_to_fert[j]->src && num < (soil_to_fert[j]->src + soil_to_fert[j]->range)) {
                    num = soil_to_fert[j]->dest + (num - soil_to_fert[j]->src);
                    break;
                }
            }
            for (int j = 0; j < len_water; j++) {
                if (num >= fert_to_water[j]->src && num < (fert_to_water[j]->src + fert_to_water[j]->range)) {
                    num = fert_to_water[j]->dest + (num - fert_to_water[j]->src);
                    break;
                }
            }
            for (int j = 0; j < len_light; j++) {
                if (num >= water_to_light[j]->src && num < (water_to_light[j]->src + water_to_light[j]->range)) {
                    num = water_to_light[j]->dest + (num - water_to_light[j]->src);
                    break;
                }
            }
            for (int j = 0; j < len_temp; j++) {
                if (num >= light_to_temp[j]->src && num < (light_to_temp[j]->src + light_to_temp[j]->range)) {
                    num = light_to_temp[j]->dest + (num - light_to_temp[j]->src);
                    break;
                }
            }
            for (int j = 0; j < len_hum; j++) {
                if (num >= temp_to_hum[j]->src && num < (temp_to_hum[j]->src + temp_to_hum[j]->range)) {
                    num = temp_to_hum[j]->dest + (num - temp_to_hum[j]->src);
                    break;
                }
            }
            for (int j = 0; j < len_loc; j++) {
                if (num >= hum_to_loc[j]->src && num < (hum_to_loc[j]->src + hum_to_loc[j]->range)) {
                    num = hum_to_loc[j]->dest + (num - hum_to_loc[j]->src);
                    break;
                }
            }

            if (i == 0) {
                min = num;
            } else {
                min = num > min ? min : num;
            }
        }
    }

    printf("The result is %ld\n",min);
    fclose(file);
    free(line);
    free(seed);
    for (int i = 0; i < len_soil; i++) {
        free(seed_to_soil[i]);
    }
    free(seed_to_soil);
    for (int i = 0; i < len_fert; i++) {
        free(soil_to_fert[i]);
    }
    free(soil_to_fert);
    for (int i = 0; i < len_water; i++) {
        free(fert_to_water[i]);
    }
    free(fert_to_water);
    for(int i = 0; i < len_light;  i++) {
        free(water_to_light[i]);
    }
    free(water_to_light);
    for(int i = 0; i < len_temp;  i++) {
        free(light_to_temp[i]);
    }
    free(light_to_temp);
    for(int i = 0; i < len_hum; i++) {
        free(temp_to_hum[i]);
    }
    free(temp_to_hum);
    for(int i = 0; i < len_loc; i++) {
        free(hum_to_loc[i]);
    }
    free(hum_to_loc);

    return 0;
}

