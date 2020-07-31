/**
 * @name: S15.8.2.16_A2;
 * @section: 15.8.2.16;
 * @assertion: If x is +0, Math.sin(x) is +0;
 * @description: Checking if Math.sin(+0) equals to +0;
 */
 
// CHECK#1
var x = +0;
if (Math.sin(x) !== +0)
{
	$ERROR("#1: 'var x = +0; Math.sin(x) !== +0'");
}