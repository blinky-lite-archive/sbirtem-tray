/*
Copyright (c) 2014, Pure Engineering LLC
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <limits.h>

static const char *device = "/dev/spidev0.1";
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 24000000;
static uint16_t delay = 0;

#define VOSPI_FRAME_SIZE (164)
uint8_t lepton_frame_packet[VOSPI_FRAME_SIZE];
static uint8_t lepton_image_buffer[38400];

int transfer(int fd)
{
	int icol;
	int irow = 0;
    uint8_t iseg;
    uint8_t segRead = 0;
	uint8_t tx[VOSPI_FRAME_SIZE] = {0, };
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)lepton_frame_packet,
		.len = VOSPI_FRAME_SIZE,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

    iseg = 0;
    while (iseg < 4)
    {
        irow = 0;
        while (irow != 59)
        {
            ioctl(fd, SPI_IOC_MESSAGE(1), &tr);

	        if(((lepton_frame_packet[0]&0xf) != 0x0f))
	        {
	            irow = lepton_frame_packet[1];
                if (irow == 20) segRead = lepton_frame_packet[0] >> 4; 
                if (irow < 60)
                {
	                for(icol = 0; icol < 80; icol++)
	                {
                        lepton_image_buffer[iseg * 9600 + irow * 160 + 2 * icol] = lepton_frame_packet[2 * icol + 4];
                        lepton_image_buffer[iseg * 9600 + irow * 160 + 2 * icol + 1] = lepton_frame_packet[2 * icol + 5];
	                }
                }
	        }
        }
        if (segRead == (iseg + 1)) ++iseg;
    }
	return 0;
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd;

    mode = 3;
	fd = open(device, O_RDWR);

	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);

	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);

	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);

    transfer(fd);

	close(fd);

    write(1,lepton_image_buffer,38400);

	return ret;
}
