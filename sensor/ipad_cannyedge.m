img_ori=imread('ipad.jpg');
img_gray=rgb2gray(img_ori);
img_gray=double(img_gray); 
col=length(img_gray(:,1));
row=length(img_gray(1,:));
figure(1);clf;imshow(uint8(img_gray))
g1=fspecial('gaussian',[5 5],1);
img1=filter2(g1,img_gray,'same');
sobelMaskx=[-1,0,1;-2,0,2;-1,0,1];
sobelMasky=[1,2,1;0,0,0;-1,-2,-1];
G_X=conv2(img1,sobelMaskx,'same');
G_Y=conv2(img1,sobelMasky,'same');
magnitude=(G_X.^2)+(G_Y.^2);
magnitude=sqrt(magnitude);
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
T_min=0.1;T_max=0.3;
T_min=T_min* max(max(BW));T_max=T_max* max(max(BW));
edge_final=zeros(col,row);
for i=1:col
    for j=1:row
        if (BW(i,j)<T_min)
            edge_final(i,j)=0;
        elseif (BW(i,j)>T_max)
            edge_final(i,j)=1;
        elseif (BW(i+1,j)>T_max || BW(i-1,j)>T_max || BW(i,j+1)>T_max ...
                || BW(i,j-1)>T_max || BW(i-1,j-1)>T_max || BW(i-1,j+1)>T_max || ...
                BW(i+1,j+1)>T_max || BW(i+1,j-1)>T_max)
            edge_final(i,j)=1;
        end
    end
end
img_canny=uint8(edge_final.*255);
output_img=img_canny;
figure();clf;imshow(output_img);title('size=5,\sigma=1,max=0.3,min=0.1');
%%
img_ori=imread('ipad.jpg');
img_gray=rgb2gray(img_ori);
img_edge=edge(img_gray,'Canny',[0.1 0.2],0.5);
figure();imshow(img_edge);