#define STB_IMAGE_IMPLEMENTATION
#include "headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "headers/stb_image_write.h"
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
    int width, height, channels;
    unsigned char *img = stbi_load("imgFiles/target.jpg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf("Error in loading the image\n");
        exit(1);
    }

    size_t img_size = width * height * channels;
    unsigned char *outputImg = malloc(img_size);
    if (outputImg == NULL)
    {
        printf("Unable to allocate memory for the grayscale image.\n");
        exit(1);
    }

    while (1)
    {
        int option;
        printf("enter the option : \n");
        printf("1. Grey Scale Filter\n");
        printf("2. Inveresion Filter\n");
        printf("3. Increase Brightness\n");
        printf("4. Increase Contrast\n");
        printf("5. Sepia Filter\n");
        scanf("%d", &option);
        if (option == 1)
        {
            for (unsigned char *p = img, *pg = outputImg; p != img + img_size; p += channels, pg += channels)
            {
                *pg = *(pg + 1) = *(pg + 2) = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
                if (channels == 4)
                {
                    *(pg + 3) = *(p + 3);
                }
            }
            break;
        }
        else if (option == 2)
        {
            for (unsigned char *p = img, *pg = outputImg; p != img + img_size; p += channels, pg += channels)
            {
                *pg = 255 - *p;
                *(pg + 1) = 255 - *(p + 1);
                *(pg + 2) = 255 - *(p + 2);
                if (channels == 4)
                {
                    *(pg + 3) = *(p + 3); // copy alpha channel
                }
            }
            break;
        }
        else if (option == 3)
        {
            int brightness = 50; // increase brightness by 50 units
            for (unsigned char *p = img, *pg = outputImg; p != img + img_size; p += channels, pg += channels)
            {
                *pg = min(255, *p + brightness);
                *(pg + 1) = min(255, *(p + 1) + brightness);
                *(pg + 2) = min(255, *(p + 2) + brightness);
                if (channels == 4)
                {
                    *(pg + 3) = *(p + 3); // copy alpha channel
                }
            }
            break;
        }
        else if (option == 4)
        {
            double contrast = 1.5; // increase contrast by 50%
            for (unsigned char *p = img, *pg = outputImg; p != img + img_size; p += channels, pg += channels)
            {
                *pg = min(255, max(0, (*p - 128) * contrast + 128));
                *(pg + 1) = min(255, max(0, (*(p + 1) - 128) * contrast + 128));
                *(pg + 2) = min(255, max(0, (*(p + 2) - 128) * contrast + 128));
                if (channels == 4)
                {
                    *(pg + 3) = *(p + 3); // copy alpha channel
                }
            }
            break;
        }
        else if (option == 5)
        {
            for (unsigned char *p = img, *pg = outputImg; p != img + img_size; p += channels, pg += channels)
            {
                unsigned char r = *p;
                unsigned char g = *(p + 1);
                unsigned char b = *(p + 2);

                *pg = min(255, (unsigned char)(0.393 * r + 0.769 * g + 0.189 * b));
                *(pg + 1) = min(255, (unsigned char)(0.349 * r + 0.686 * g + 0.168 * b));
                *(pg + 2) = min(255, (unsigned char)(0.272 * r + 0.534 * g + 0.131 * b));

                if (channels == 4)
                {
                    *(pg + 3) = *(p + 3); // copy alpha channel
                }
            }
            break;
        }
        else if (option == 5)
        {
            for (unsigned char *p = img, *pg = outputImg; p != img + img_size; p += channels, pg += channels)
            {
                unsigned char r = *p;
                unsigned char g = *(p + 1);
                unsigned char b = *(p + 2);

                *pg = min(255, (unsigned char)(0.393 * r + 0.769 * g + 0.189 * b));
                *(pg + 1) = min(255, (unsigned char)(0.349 * r + 0.686 * g + 0.168 * b));
                *(pg + 2) = min(255, (unsigned char)(0.272 * r + 0.534 * g + 0.131 * b));

                if (channels == 4)
                {
                    *(pg + 3) = *(p + 3); // copy alpha channel
                }
            }
            break;
        }
        else
        {
            printf("please enter a valid input");
            continue;
        }
    }

    stbi_write_jpg("imgFiles/output.jpg", width, height, channels, outputImg, 100);

    stbi_image_free(img);
    free(outputImg);

    return 0;
}
