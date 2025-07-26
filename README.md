# Linear Filters in Image Processing
Enhancing and extracting image features through classical convolution-based filtering.

*Supports GRAYSCALE images only*

---

## Before vs After

| Original | Filtered |
|----------|----------|
| ![original](images/cat.png) | ![filtered](images/cat_filtered.png) |
| ![original](images/road.png) | ![filtered](images/road_filtered.png) |
| ![original](images/face.png) | ![filtered](images/face_filtered.png) |

---

## Features

- **Gaussian Blur**: Softens images and removes high-frequency noise  
- **Box Filter**: Simple average blur  
- **Edge Detection**: Using first derivative filters (Sobel, Prewitt, Scharr)  
- **Second Derivative Filters**: Laplacian operator for blob/energy detection  
- **Smoothing / Denoising**: Reduces visual noise using convolution  
- **Steerable Filters**: Edge/structure detection at arbitrary orientations  
- **Custom Convolution Support**: Plug your own kernel  
- **STB PNG Support**: Image loading/saving using `stb_image` and `stb_image_write`

---

## How to Use

1. Load your PNG image with:  
   ```cpp
   PngImage img = load_png("input.png");


## How It Works

### Step 1: Tile Division
Divide the image into square tiles of size **M × M**.  
- `M` is a user-defined parameter (e.g., 64, 128).

---

### Step 2: Histogram & Clipping
For each tile and for each color channel:
- Compute the histogram.
- Apply **clipping**:  
  Clip any bin value above a clip limit and accumulate the **total excess**.  
  - **Clip limit** = (tile width × tile height) / **clip factor**
  - **Clip factor** is a user-defined parameter.

---

### Step 3: Redistribute Excess
- Distribute the **total excess** equally across all 256 bins:
  - `excess per bin = total excess / 256`
- Add this redistributed excess to the original (clipped) histogram bins.

---

### Step 4: Cumulative Distribution Function (CDF)
- Calculate the **cumulative distribution** from the histogram:
  ```
  c(0) = H(0) / N  
  c(i) = c(i-1) + H(i) / N
  ```
  where `N = tile width × tile height`

---

### Step 5: Histogram Equalization
Apply a blend of the equalized value and the original intensity:
  ```
  HE(i) = alpha * c(i) * i + (1 - alpha) * i
  ```
- `alpha` is the **blend** parameter in range [0.0, 1.0]  
  - 1.0 = full equalization  
  - 0.0 = original image

---

### Step 6: Interpolation
To avoid visible borders between tiles, interpolate the result for each pixel from the 4 surrounding tiles using bilinear interpolation:

```
y
↑
|   (0,1)          (1,1)
|    HE10         HE11
|      +------------+
|      |            |
|      |   (fx,fy)  |
|      |            |
|      +------------+
|   (0,0)          (1,0)
|    HE00         HE01
+------------------------→ x

P[i] =
  (1 - fx) * (1 - fy) * HE00[i] +
  fx * (1 - fy) * HE01[i] +
  (1 - fx) * fy * HE10[i] +
  fx * fy * HE11[i];
```

---

### Step 7: Done
Enjoy the adaptively equalized image with improved contrast and brightness :)

---

## Parameters to Tune

| Parameter     | Description                                 |
|---------------|---------------------------------------------|
| Tile Size `M` | Size of each square tile                    |
| Clip Factor   | Lower = more aggressive clipping            |
| Alpha         | Blend between original and equalized image |

---

*Developed by Mohammed Yasser Mohammed* 

*email : es-mohamed.yasser2027@alexu.edu.eg* 
