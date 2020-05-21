var SPI = require('pi-spi');
var fs = require("fs");
var spi = SPI.initialize("/dev/spidev0.1");

spi.clockSpeed(16000000);
//console.log(spi.clockSpeed());
var imgData = [];
for (var ii = 0; ii < 60; ++ii) imgData[ii] = [];
var dataView     = new DataView(new ArrayBuffer(2));
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
        		var frame_number = dataBufRead[1];
                for ( var ii = 0; ii < 80; ++ii)
                {
                    dataView.setUint8(0, dataBufRead[ii * 2 + 4]);
                    dataView.setUint8(1, dataBufRead[ii * 2 + 5]);
                    imgData[frame_number][ii] = dataView.getUint16(0);
                }
                
//                console.log();
//                console.log(temp);
//                console.log(frame_number);
                if (frame_number < 59)
                {
                    readSpiLine();
                }
                else
                {
                    printFile();
                }
            }
            else
            {
                readSpiLine();
            }
        }
    );
}
function printFile()
{
    var minval = imgData[0][0];
    var maxval = imgData[0][0];
    for (var irow = 0; irow < 60; ++irow)
    {
        for(var icol = 0; icol < 80; ++icol)
        {
            if ( minval > imgData[irow][icol]) minval = imgData[irow][icol];
            if ( maxval < imgData[irow][icol]) maxval = imgData[irow][icol];
        }
    }
    var fileContents = 'P2\n80 60\n' + (maxval - minval).toString() + '\n ';
    for (var irow = 0; irow < 60; ++irow)
    {
        for(var icol = 0; icol < 80; ++icol)
        {
            fileContents = fileContents + (imgData[irow][icol] - minval).toString() + ' ';
        }
        fileContents = fileContents + '\n';
    }
    
    fs.open('flir25.pgm', 'w', function (err, file) {if (err) throw err;});

    fs.appendFile('flir25.pgm', fileContents, function (err) {if (err) throw err;});
}

