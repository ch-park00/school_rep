%%
clear;clc;
rgb_image=imread('AVM_image.png');
hsv_image=rgb2hsv(rgb_image);

H=hsv_image(:,:,1);
S=hsv_image(:,:,2);
V=hsv_image(:,:,3);

H_thr_l= 0.1 ; H_thr_h= 0.2 ;
S_thr_l= 0.2 ; S_thr_h= 1 ;
V_thr_l= 0.2 ; V_thr_h= 1 ;

H_thr=(H_thr_l < H & H < H_thr_h);
S_thr=(S_thr_l < S & S < S_thr_h);
V_thr=(V_thr_l < V & V < V_thr_h);

bin_img=H_thr&S_thr&V_thr;
figure();imshow(bin_img);
figure();imshow(rgb_image);