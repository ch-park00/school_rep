%%
clear;clf;close all;

img_ori=imread('lanedetect.bmp');
img_gray=rgb2gray(img_ori);
img_gray=double(img_gray); %0-255 사이 값을 0-1 사이 값으로 바꿔줌.

figure(1);clf;imshow(uint8(img_gray));

col=length(img_gray(:,1));
row=length(img_gray(1,:));
% 이미지를 절반으로 나눠 아래 부분만 사용
img_gray=img_gray(col/2:col,1:row);
figure(2);clf;imshow(uint8(img_gray))

%%
g1=fspecial('gaussian',[5,5],5);
g2=fspecial('gaussian',[5,5],10);
g3=fspecial('gaussian',[11,11],5);

img1=filter2(g1,img_gray,'same'); %filter2 : x,y 방향 동시에 필터링.이미지 프로세싱 때 사용됨.
img2=filter2(g2,img_gray,'same'); 
img3=filter2(g3,img_gray,'same');

figure(3);clf;
subplot(221);imshow(uint8(img_gray));
title('Original image','Fontsize',10);
subplot(222); imshow(uint8(img1));
title('Gaussian filtered image, size=5X5, \sigma=5','Fontsize',10);

subplot(223); imshow(uint8(img2));
title('Gaussian filtered image, size=5X5, \sigma=10','Fontsize',10);

subplot(224); imshow(uint8(img3));
title('Gaussian filtered image, size=11X11, \sigma=5','Fontsize',10);

sobelMaskx=[-1,0,1;-2,0,2;-1,0,1];
sobelMasky=[1,2,1;0,0,0;-1,-2,-1];

G_X=conv2(img1,sobelMaskx,'same');
G_Y=conv2(img1,sobelMasky,'same');
figure(7);clf;subplot(211);imshow(uint8(G_X));title('G_X');subplot(212);imshow(uint8(G_Y));title('G_Y');

magnitude=(G_X.^2)+(G_Y.^2);
magnitude=sqrt(magnitude); %  유클리드 거리를 구함=> 대각선 거리를 구함.(edge의 크기=강도(얼마나 흰색인지)를 확인한다.)
figure(8);clf;imshow(uint8(magnitude));title('magnitude');
figure(4);clf;imshow(uint8(G_Y));

theta=atan2(G_Y,G_X);
theta=theta*180/pi;
col=length(img_gray(:,1));
row=length(img_gray(1,:));
for i=1:col
        for j=1:row
            if (theta(i,j)<0)
                theta(i,j)=360+theta(i,j);
            end
        end
end

qtheta=zeros(col,row);
for i=1:col
    for j=1:row
        if (((theta(i,j)>=0) && (theta(i,j) <22.5)) || ...
                ((theta(i,j)>=157.5) && (theta(i,j)<202.5)) || ...
                ((theta(i,j)>=337.5) && (theta(i,j)<=360)))
            qtheta(i,j)=0;
        elseif (((theta(i,j)>=22.5) && (theta(i,j) <67.5)) || ...
                ((theta(i,j)>=202.5) && (theta(i,j)<247.5)))
            qtheta(i,j)=1;
        elseif (((theta(i,j)>=67.5) && (theta(i,j) <112.5)) || ...
                ((theta(i,j)>=247.5) && (theta(i,j)<292.5)))
            qtheta(i,j)=2;
        elseif (((theta(i,j)>=112.5) && (theta(i,j) <157.5)) || ...
                ((theta(i,j)>=292.5) && (theta(i,j)<337.5)))
            qtheta(i,j)=3;
        end
    end
end

BW=zeros(col,row);
for i=2:col-1
    for j=2:row-1
        if (qtheta(i,j)==0)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i,j+1),magnitude(i,j-1)]));
        elseif (qtheta(i,j)==1)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i+1,j-1),magnitude(i-1,j+1)]));
        elseif (qtheta(i,j)==2)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i+1,j),magnitude(i-1,j)]));
        elseif (qtheta(i,j)==3)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i+1,j+1),magnitude(i-1,j-1)]));
        end
    end
end
BW=BW.*magnitude;

T_min=0.1;T_max=0.2;
T_min=T_min* max(max(BW));T_max=T_max* max(max(BW)); %2D의 최대값 찾음.
edge_final=zeros(col,row);
for i=1:col
    for j=1:row
        if (BW(i,j)<T_min) %최저 임계점 미만
            edge_final(i,j)=0;
        elseif (BW(i,j)>T_max) %최대 임계점 초과
            edge_final(i,j)=1;
        elseif (BW(i+1,j)>T_max || BW(i-1,j)>T_max || BW(i,j+1)>T_max ...
                || BW(i,j-1)>T_max || BW(i-1,j-1)>T_max || BW(i-1,j+1)>T_max || ...
                BW(i+1,j+1)>T_max || BW(i+1,j-1)>T_max) %자신 이외의 8개의 인근 픽셀이 최대 임계점 초과시 현재 픽셀 엣지로 사용.
            edge_final(i,j)=1;
        end
    end
end
img_canny=uint8(edge_final.*255);
output_img=img_canny;
figure(5);clf;imshow(output_img);
img_ori=imread('lanedetect.bmp');
img_gray=rgb2gray(img_ori);
img_gray=img_gray(length(img_gray(:,1))/2:end,1:end);
img_edge=edge(img_gray,'Canny',[0.1 0.2],0.5);
figure(6);imshow(img_edge);
%%
clear;clc;
sig=[0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,];
d_sig=diff(sig);
dd_sig=diff(d_sig);
figure(1);subplot(311);plot(sig);subplot(312);plot(d_sig);subplot(313);plot(dd_sig)

%% hough transform - 0514
clear all;close all;figure(1);clf;grid on;

X=[];Y=[];

while(length(X) < 11)
    figure(1);
    set(gca,'Ydir','reverse');set(gca,'XAxisLocation','top');
    xlim([0 100]);ylim([0 100]);
    
    [x,y]=getpts;
    x=ceil(x); y=ceil(y);
    X=[X; x]; Y=[Y;y];
    clf;
    
    for i=1:length(X)
        plot(X(i),Y(i),'.','Markersize',20);hold on;grid on;
    end
    theta=-90:0.1:90;
    Rho=X*cos(theta*pi/180) + Y*sin(theta*pi/180);
    
    figure(2);clf;plot(theta,Rho);hold on;grid on;
    xlim([-91 91]);ylim([-sqrt(2)*100 sqrt(2)*100]);
end

%% 0516
% H = 허프 공간상 점의 개수 , T=theta, R=거리
[H,T,R]= hough(img_canny);
% 35 = max number of peaks.
P=houghpeaks(H,35,'threshold',ceil(0.3*max(H(:))));

% fillgap= 선은 라인 두개가 있는데 이를 하나로 합친다. minlength=이 값 이내라면 라인 하나로 취급
[lines]=houghlines(img_canny,T,R,P,'FillGap',10,'Minlength',8);

c1=[];c2=[];l=[];

for k=1:length(lines)
    c1=[c1;[lines(k).point1 3]];
    c2=[c2;[lines(k).point2 3]];
    
    l=[l;lines(k).point1 lines(k).point2];
end

img_line=insertShape(uint8(img_gray),'Line',l,'color','green','Linewidth',3);

img_line=insertShape(uint8(img_line),'Circle',c1,'color','red');

img_line=insertShape(uint8(img_line),'Circle',c2,'color','yellow');

figure(10);
imshow(img_line);