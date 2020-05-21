var SPI = require('pi-spi');
var fs = require("fs");
var spi = SPI.initialize("/dev/spidev0.1");

spi.clockSpeed(16000000);
//console.log(spi.clockSpeed());
var imgData = Buffer.alloc(9600);
for (var ii = 0; ii < 60; ++ii) imgData[ii] = [];
var dataBufWrite = Buffer.alloc(164);
readSpiLine();
function readSpiLine()
{
    dataBufWrite[0] = 0;
    spi.transfer(dataBufWrite, 164, 
        function(err, dataBufRead)
        {
    	    if(((dataBufRead[0] & 0xf) != 0x0f))
    	    {
        		var frameNumber = dataBufRead[1];
                for ( var ii = 0; ii < 80; ++ii)
                {
                    imgData[frameNumber * 160 + ii * 2]     = dataBufRead[ii * 2 + 4]
                    imgData[frameNumber * 160 + ii * 2 + 1] = dataBufRead[ii * 2 + 5]
                }
                
                if (frameNumber < 59)
                {
                    readSpiLine();
                }
                else
                {
                    process.stdout.write(imgData);
                }
            }
            else
            {
                readSpiLine();
            }
        }
    );
}

