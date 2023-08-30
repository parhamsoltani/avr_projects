#pragma used+

void at24c512_write(unsigned char device_addr, 
                    unsigned int data_addr, 
                    unsigned char *buffer, 
                    unsigned char count);
void at24c512_read(unsigned char device_addr, 
                    unsigned int data_addr, 
                    unsigned char *buffer, 
                    unsigned char count);

#pragma used-
#pragma library at24c512.lib