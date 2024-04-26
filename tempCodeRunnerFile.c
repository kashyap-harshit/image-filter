for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += channels) {
        *pg = *(pg+1) = *(pg+2) = (uint8_t)((*p + *(p+1) + *(p+2))/3.0);
        if(channels == 4) {
            *(pg+3) = *(p+3);
        }
    }