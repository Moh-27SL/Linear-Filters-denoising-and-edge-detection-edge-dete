# Linear Filters in Image Processing
Enhancing and extracting image features through classical convolution-based filtering.

*Supports GRAYSCALE images only, and uses clamping not padding in convolution*

---

## Denoising

| Original | Moving average | gaussian |
|----------|----------------|----------|
| ![original](result/Denoising/lena.png) | ![moving average](result/Denoising/smoothing_weighted_average.png) | ![gaussian](result/Denoising/smoothing_gaussian.png) |

## Blurring

| Original | Moving average | gaussian |
|----------|----------------|----------|
| ![original](result/Denoising/lena.png) | ![moving average](result/Denoising/blurring_weighted_average.png) | ![gaussian](result/Denoising/blurring_gaussian.png) |

## Edge Detection Steerable 
*first partial derivative wrt direction, Gaussian*

| Original | 0 deg | pi/2 deg | pi/4 deg |
|----------|-------|----------|----------|
| ![original](result/steerable_filters/shape.png) | ![0 deg](result/steerable_filters/Edge_0.png) | ![90 deg](result/steerable_filters/Edge_90.png) | ![45 deg](result/steerable_filters/Edge_45.png) |

## Shape Detection Steerable 
*second partial derivative wrt direction, Gaussian*

| Original | 0 deg | pi/2 deg | pi/4 deg |
|----------|-------|----------|----------|
| ![original](result/steerable_filters/shape.png) | ![0 deg](result/steerable_filters/shape_sec_90.png) | ![90 deg](result/steerable_filters/shape_sec_45.png) | ![45 deg](result/steerable_filters/shape_sec_0.png) |

---

## Features

- **Gaussian Blur**: Softens images and removes high-frequency noise  
- **moving average**: Simple average blur  
- **Steerable Filters**: Edge/structure detection at arbitrary orientations  
- **Custom Convolution Support**: Plug your own kernel  

---

## How to Use

1. get the data from the image
2. Apply the desired filter, for example :
   ```cpp
   unsigned char* convolve(img, gaussian_kernel, size);
4. enjoy :)


---
## Parameters to Tune

| Parameter     | Description                                             |
|---------------|---------------------------------------------------------|
| Kernel Size   | Size of the filter (e.g. 3×3, 5×5). Affects smoothing   |
| Sigma         | Standard deviation for Gaussian blur. *(3 \* sigma = 1/2 kernal_length)* |
| Angle         | Orientation angle for steerable filters (in degrees)    |

---

*Developed by Mohammed Yasser Mohammed* 

*email : es-mohamed.yasser2027@alexu.edu.eg* 
