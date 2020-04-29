# NoiseAnalyzer
NoiseAnalyzer - Gaussian Noise Analyze ( support Hevc all-intra Compression Noise )

# Noise Modeling

we can design following noise model.

![image](./IMG/Noise.png)

# Generate Gaussian Noise 

define Noise Level and generate gaussian noise.

![image](./img/NoiseLevel.Png)



# Display Histogram

Histogram is used as a way to analyze noise. 

## Pixel Histogram

Available when setting window size to 1. 

![image](./img/Histogram.png)

## Local Variance Histogram

1. set window size ! 
2. The local variance image is obtained as shown below. 

![image](./img/LVH.png)

![image](./img/LVH_hist.png)

# Demo

![image](./img/Demo.gif)



# Reference

* Local histogram figrue
  * <https://www.researchgate.net/figure/Noise-histogram-estimation_fig1_46137484> 

