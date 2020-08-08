function output_img = Canny_acl(src_img ,filtersz, gamma, th_h, th_l)
%CANNY_ACL 이 함수의 요약 설명 위치
%   자세한 설명 위치

%% gaussian filter
g1 = fspecial('gaussian', [filtersz, filtersz], gamma);

img1 = filter2(g1,src_img);

%% Calculating gradient with sobel mask
sobelMaskX = [-1, 0, 1; -2, 0, 2; -1, 0, 1];
sobelMaskY = [1, 2, 1; 0, 0, 0; -1, -2, -1];

%Convolution by image by horizontal and vertical filter
G_X = conv2(img1, sobelMaskX, 'same');
G_Y = conv2(img1, sobelMaskY, 'same');

%Calcultae magnitude of edge
magnitude = (G_X.^2) + (G_Y.^2);
magnitude = sqrt(magnitude);

%Calculate directions/orientations
theta = atan2 (G_Y, G_X);
theta = theta*180/pi;

%Adjustment for negative directions, making all directions positive
col = length(src_img(:,1));
row = length(src_img(1,:));
for i=1:col
    for j=1:row
        if (theta(i,j)<0) 
            theta(i,j)=360+theta(i,j);
        end;
    end;
end;

%% quantization theta

qtheta = zeros(col, row);

%Adjusting directions to nearest 0, 45, 90, or 135 degree
for i = 1  : col
    for j = 1 : row
        if ((theta(i, j) >= 0 ) && (theta(i, j) < 22.5) || (theta(i, j) >= 157.5) && (theta(i, j) < 202.5) || (theta(i, j) >= 337.5) && (theta(i, j) <= 360))
            qtheta(i, j) = 0; % degree 0
        elseif ((theta(i, j) >= 22.5) && (theta(i, j) < 67.5) || (theta(i, j) >= 202.5) && (theta(i, j) < 247.5))
            qtheta(i, j) = 1; % degree 1
        elseif ((theta(i, j) >= 67.5 && theta(i, j) < 112.5) || (theta(i, j) >= 247.5 && theta(i, j) < 292.5))
            qtheta(i, j) = 2; % degree 2
        elseif ((theta(i, j) >= 112.5 && theta(i, j) < 157.5) || (theta(i, j) >= 292.5 && theta(i, j) < 337.5))
            qtheta(i, j) = 3; % degree 3
        end;
    end;
end;

BW = zeros (col, row);

%% Non-Maximum Supression

BW = zeros (col, row);
for i=2:col-1
    for j=2:row-1
        if (qtheta(i,j)==0)
            BW(i,j) = (magnitude(i,j) == max([magnitude(i,j), magnitude(i,j+1), magnitude(i,j-1)]));
        elseif (qtheta(i,j) == 1)
            BW(i,j) = (magnitude(i,j) == max([magnitude(i,j), magnitude(i+1,j-1), magnitude(i-1,j+1)]));
        elseif (qtheta(i,j) == 2)
            BW(i,j) = (magnitude(i,j) == max([magnitude(i,j), magnitude(i+1,j), magnitude(i-1,j)]));
        elseif (qtheta(i,j) == 3)
            BW(i,j) = (magnitude(i,j) == max([magnitude(i,j), magnitude(i+1,j+1), magnitude(i-1,j-1)]));
        end;
    end;
end;

BW = BW.*magnitude; 

%% Hysteresis Thresholding

T_min = th_h;
T_max = th_l;

%Hysteresis Thresholding
T_min = T_min * max(max(BW));
T_max = T_max * max(max(BW));

edge_final = zeros (col, row);

for i = 1  : col
    for j = 1 : row
        % no edge
        if (BW(i, j) < T_min) 
            edge_final(i, j) = 0;
        % Strong edge
        elseif (BW(i, j) > T_max)
            edge_final(i, j) = 1;
        % Weak edge - Using 8-connected components 
        elseif ( BW(i+1,j)>T_max || BW(i-1,j)>T_max || BW(i,j+1)>T_max || BW(i,j-1)>T_max || BW(i-1, j-1)>T_max || BW(i-1, j+1)>T_max || BW(i+1, j+1)>T_max || BW(i+1, j-1)>T_max)
            edge_final(i,j) = 1;
        end;
    end;
end;

img_canny = uint8(edge_final.*255);
output_img = img_canny;
end

