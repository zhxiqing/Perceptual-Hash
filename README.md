# Perceptual-Hash
## The search for similar wallpaper
This is a Transverse project of students of Polytech Nantes.
The company who gives the suject : Quai des apps (https://www.quai-des-apps.com/realisation)

The goal is to search the similar wallpapers when given a motif that we like. We would like to simulate the human perception using the Hash fonction. So we transform the image into descriptor, and for the moment, we have HTD(Homogeneous Texture Descriptor) and CLD(Color Structure Descriptor). We also combine these two descriptor to find the best ratio.

For the hash fonction, we use the algorithm of MPEG7 which gives many images descriptor. And the implementation of these algorithm is written by Muhammet Bastan, you can find here: https://github.com/cdmh/MPEG7FexLib

Library dependence: OpenCV 2.4.13

The programe is divided into two part. 
The first part is to calcule all the descriptors of images, and save in a file text, you can find all code sources in "PerceptualHashCodeSource.rar". 
The seconde part is to calcule the distance between the descriptors and vary different ratio of two types decriptor, and give the result by a file csv. You can find the project VS2015 in DistanceDCT.

"ProjetPTransQuaidesApps2016-2017.pdf" is the document of the project, you can find some introduce of mannagement of our project and the algorithms.

"DocumentationOUTILPTRANS.pdf" introduces how to use the code.

"Interpetation.xlsx" is the result which apply the program to our images.

"OpenCVx86VC14" is the file which you can find OpenCV2.4.13 compiled for VS2015, if you don't want to complie OpenCV yourself, you can use it directly. To download OpenCV : http://opencv.org/

"Images" if the file which contain our test base,  the file "resemblance.txt" describe the similarity of humain perception, the number is the number of images, and the first number of every line is the image that we search.

If any question, please contact:

etienne.martin2@etu.univ-nantes.fr
xiqing.zhang@etu.univ-nantes.fr







