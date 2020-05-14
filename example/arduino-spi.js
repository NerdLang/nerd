var arduino = require("arduino");

var spi = require("arduino-spi");

function setup()
{
    spi.beginTransaction(14000, MSBFIRST, SPI_MODE0);
}

function loop()
{

}