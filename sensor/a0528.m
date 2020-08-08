%%
clear;close all;clc
load cameraParams1
img_front=imread('front.jpg');
img_rear=imread('back.jpg');
img_left=imread('left.jpg');
img_right=imread('right.jpg');
car=imread('car.bmp');
car1=imresize(car,[500 180]);
undistorted = undistortFisheyeImage(img_front,cameraParams1.Intrinsics,'ScaleFactor',0.5);
undistorted1 = undistortFisheyeImage(img_rear,cameraParams1.Intrinsics,'ScaleFactor',0.5);
undistorted2 = undistortFisheyeImage(img_left,cameraParams1.Intrinsics,'ScaleFactor',0.5);
undistorted3 = undistortFisheyeImage(img_right,cameraParams1.Intrinsics,'ScaleFactor',0.5);
undistorted1_rot=imrotate(undistorted1,180);
undistorted2_rot=imrotate(undistorted2,90);
undistorted3_rot=imrotate(undistorted3,-90);
imshow(undistorted1_rot);
%% front
A1=[254,302;447,310;550,397;198,359];
B1=[160,160;340,160;340,220;160,220];
Tf1=fitgeotrans(A1,B1,'projective');
l_ref1=imref2d([250 500]);
l1=imwarp(undistorted,Tf1,'Outputview',l_ref1);
figure();imshow(l1);
%% back
A2=[173,76;394,106;355,207;244,206];
B2=[190,0;310,0;310,60;190,60];
Tf2=fitgeotrans(A2,B2,'projective');
l_ref2=imref2d([250 500]);
l2=imwarp(undistorted1_rot,Tf2,'Outputview',l_ref2);
figure();imshow(l2);
%% left
A3=[212,327;396,336;395,488;228,421];
B3=[70,210;160,210;160,330;70,330];
Tf3=fitgeotrans(A3,B3,'projective');
l_ref3=imref2d([500 160]);
l3=imwarp(undistorted2_rot,Tf3,'Outputview',l_ref3);
figure();imshow(l3)
%% right
A4=[66,133;273,230;240,437;66,525];
B4=[0,120;90,120;90,300;0,300];
Tf4=fitgeotrans(A4,B4,'projective');
l_ref4=imref2d([500 160]);
l4=imwarp(undistorted3_rot,Tf4,'Outputview',l_ref4);
figure();imshow(l4)
%%
final=horzcat(l3,car1,l4);
final1=vertcat(l1,final,l2);
figure();imshow(final1);