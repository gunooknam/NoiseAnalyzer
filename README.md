# NoiseAnalyzer
NoiseAnalyzer - Gaussian Noise Analyze ( support Hevc all-intra Compression Noise )

# Noise Modeling

we can design following noise model.

![image](./img/Noise.PNG)

# Generate Gaussian Noise 

define Noise Level and generate gaussian noise.

![image](./img/NoiseLevel.PNG)



# Display Histogram

Histogram is used as a way to analyze noise. 

## Pixel Histogram

Available when setting window size to 1. 

![image](./img/Histogram.PNG)

## Local Variance Histogram

1. set window size ! 
2. The local variance image is obtained as shown below. 

![image](./img/LVH.PNG)

![image](./img/LVH_hist.PNG)

# Demo

![image](./img/Demo.gif)



# Reference

* Local Variance histogram figure
  * <https://www.researchgate.net/figure/Noise-histogram-estimation_fig1_46137484> 

