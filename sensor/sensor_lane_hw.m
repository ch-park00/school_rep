%% 
clear;
% 사진 읽기
img_ori=imread('lane0511.jpg');
% rgb 3채널의 값을 1채널로 변경.
img_gray=rgb2gray(img_ori);
% 이후 계산을 위해 자료형을 double로 변경
img_gray=double(img_gray); 
col=length(img_gray(:,1));
row=length(img_gray(1,:));
% 사진 중 아래쪽 절반만 사용
img_gray=img_gray(col/2:col,1:row);
figure(1);clf;imshow(uint8(img_gray))
% 가우시안 필터. 사이즈=5, σ=5
g1=fspecial('gaussian',[3 3],5);
% 이미지에 가우시안 필터 적용. 이미지가 약간 블러 처리되면서
% 노이즈가 죽는다.
img1=filter2(g1,img_gray,'same');
% 소벨 마스크를 통해 공간상의 엣지를 검출한다
sobelMaskx=[-1,0,1;-2,0,2;-1,0,1];
sobelMasky=[1,2,1;0,0,0;-1,-2,-1];
G_X=conv2(img1,sobelMaskx,'same');
G_Y=conv2(img1,sobelMasky,'same');
magnitude=(G_X.^2)+(G_Y.^2);
%  유클리드 거리를 구함=> 대각선 거리를 구함.(edge의 크기=강도(얼마나 흰색인지)를 확인한다.)
magnitude=sqrt(magnitude); 
theta=atan2(G_Y,G_X);
theta=theta*180/pi;
col=length(img_gray(:,1));
row=length(img_gray(1,:));
% atan2 출력값이 음수인 경우도 있으므로 이 경우 360을 더해 theta값을 0~360 사이로 만들어준다.
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
        if (((theta(i,j)>=0) && (theta(i,j) <22.5)) ||...
                ((theta(i,j)>=157.5) && (theta(i,j)<202.5)) ||...
                ((theta(i,j)>=337.5) && (theta(i,j)<=360)))
            qtheta(i,j)=0;
        elseif (((theta(i,j)>=22.5) && (theta(i,j) <67.5)) ...
                || ((theta(i,j)>=202.5) && (theta(i,j)<247.5)))
            qtheta(i,j)=1;
        elseif (((theta(i,j)>=67.5) && (theta(i,j) <112.5))...
                || ((theta(i,j)>=247.5) && (theta(i,j)<292.5)))
            qtheta(i,j)=2;
        elseif (((theta(i,j)>=112.5) && (theta(i,j) <157.5)) ...
                || ((theta(i,j)>=292.5) && (theta(i,j)<337.5)))
            qtheta(i,j)=3;
        end
    end
end
% 앞에서 나온 theta값을 바탕으로 구간을 나눠 해당 구간에 해당하는 값을 매겨 그룹화.
% 주변 픽셀을 보고 판단
BW=zeros(col,row);
for i=2:col-1
    for j=2:row-1
        % 수평방향 직선
        if (qtheta(i,j)==0)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i,j+1),magnitude(i,j-1)]));
        % 3시방향으로 기운 직선
        elseif (qtheta(i,j)==1)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i+1,j-1),magnitude(i-1,j+1)]));
        % 수직방향 직선
        elseif (qtheta(i,j)==2)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i+1,j),magnitude(i-1,j)]));
        % 9시방향 직선
        elseif (qtheta(i,j)==3)
            BW(i,j)=(magnitude(i,j)==max([magnitude(i,j),magnitude(i+1,j+1),magnitude(i-1,j-1)]));
        end
    end
end
BW=BW.*magnitude;
% 최소 임계점과 최대 임계점을 지정.
T_min=0.1;T_max=0.4;
T_min=T_min* max(max(BW));T_max=T_max* max(max(BW)); %2D의 최대값 찾음.
edge_final=zeros(col,row);
for i=1:col
    for j=1:row
        % 최저 임계점 미만
        if (BW(i,j)<T_min) 
            edge_final(i,j)=0;
        % 최대 임계점 초과
        elseif (BW(i,j)>T_max) 
            edge_final(i,j)=1;
        % 그 중간에 있는 경우 주위에 edge인 픽셀이 있는지 보고 판단
        elseif (BW(i+1,j)>T_max || BW(i-1,j)>T_max || BW(i,j+1)>T_max ...
                || BW(i,j-1)>T_max || BW(i-1,j-1)>T_max || BW(i-1,j+1)>T_max || ...
                BW(i+1,j+1)>T_max || BW(i+1,j-1)>T_max) %자신 이외의 8개의 인근 픽셀이 최대 임계점 초과시 현재 픽셀 엣지로 사용.
            edge_final(i,j)=1;
        end
    end
end
% 결과 출력
img_canny=uint8(edge_final.*255);
output_img=img_canny;
figure();clf;imshow(output_img);title('size=3,\sigma=5,max=0.4,min=0.1');
%% 매트랩에 내장되어 있는 edge함수 사용해 edge 검출.
img_ori=imread('lane0511.jpg');
img_gray=rgb2gray(img_ori);
img_gray=img_gray(length(img_gray(:,1))/2:end,1:end);
img_edge=edge(img_gray,'Canny',[0.1 0.2],0.5);
figure();imshow(img_edge);
