# Barcode-Code128

Program encoding a messange or code into a code128 barcode. Padding, height and dimention multiplier of the image can be changed.


## How to use</h4>

Program runs only in command line or shell. The argument as the message, code to convert and optional parameters as image height, dimention multiplier and file name are given after a program path. </br>

```Ex. C:\test>Barcode-Code128.exe test -h 80 -p 11 -m 3 -f test```</br>

Results:</br>
Padding: 11px</br>
Dimention multiplier: 3</br>
Width: of the image: (2 * 11 + 79) * 3 = 303px</br>
Height of the image: 80 * 3 = 240px</br>
Image file name: test.png</br>
Image:</br>
![test](https://github.com/Wicio05/Barcode-code128/assets/95180248/b6c9949d-8c99-41ef-afa0-94d087f18f16)

</p>
</div>

### External libraries
This progrma uses <a href="https://lodev.org/lodepng/">lodepng</a> for making an image.
