## parallelimagefilter
It is an imagefilter written in c using threadpool.
It takes a p3.ppm image and with kernel convolution a small grid of numbers is passed over the whole image.
Than it is tansforming it passed on what those numbers are, and outputs a new image.
By using a 3x3 kernel like -1,-1,-1,-1,8,-1,-1,-1,-1 we can perform edge detection.
And by using other numbers in the kernel, we can perform blurs, sharpen and other filters.
A threadpool is used to parappelize the work and make it faster.
