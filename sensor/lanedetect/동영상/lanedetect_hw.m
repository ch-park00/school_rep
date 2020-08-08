%%
close all;clear;clc;
filename = 'challenge.mp4';
VideoSource = vision.VideoFileReader(filename, 'VideoOutputDataType', 'double');
VideoOut = vision.VideoPlayer('Name', 'Output');
VideoOut2 = vision.VideoPlayer('Name', 'Canny');
while ~isDone(VideoSource)
    img = step(VideoSource);
    img_ori = imresize(img, 0.5);
    col = length(img_ori(:,1));
    row = length(img_ori(1,:));
    img_ori = imcrop(img_ori,[1 col/2 row col/2]);
    img_gray = rgb2gray(img_ori);
    
    % line detection °úÁ¤
    img_gray = double(img_gray);
    g1 = fspecial('gaussian', [10, 10], 10);
    img1 = filter2(g1,img_gray);
    sobelMaskX = [-1, 0, 1; -2, 0, 2; -1, 0, 1];
    sobelMaskY = [1, 2, 1; 0, 0, 0; -1, -2, -1];
    G_X = conv2(img1, sobelMaskX, 'same');
    G_Y = conv2(img1, sobelMaskY, 'same');
    magnitude = (G_X.^2) + (G_Y.^2);
    magnitude = sqrt(magnitude);
    theta = atan2 (G_Y, G_X);
    theta = theta*180/pi;
    col = length(img_gray(:,1));
    row = length(img_gray(1,:));
    for i=1:col
        for j=1:row
            if (theta(i,j)<0)
                theta(i,j)=360+theta(i,j);
            end
        end
    end
    for i = 1  : col
        for j = 1 : row
            if ((theta(i, j) >= 0 ) && (theta(i, j) < 22.5) ||...
                    (theta(i, j) >= 157.5) && (theta(i, j) < 202.5) ...
                    || (theta(i, j) >= 337.5) && (theta(i, j) <= 360))
                qtheta(i, j) = 0; 
            elseif ((theta(i, j) >= 22.5) && (theta(i, j) < 67.5) || ...
                    (theta(i, j) >= 202.5) && (theta(i, j) < 247.5))
                qtheta(i, j) = 1; 
            elseif ((theta(i, j) >= 67.5 && theta(i, j) < 112.5) ||...
                    (theta(i, j) >= 247.5 && theta(i, j) < 292.5))
                qtheta(i, j) = 2; 
            elseif ((theta(i, j) >= 112.5 && theta(i, j) < 157.5) ||...
                    (theta(i, j) >= 292.5 && theta(i, j) < 337.5))
                qtheta(i, j) = 3; 
            end
        end
    end
    
    BW = zeros (col, row);
    for i=2:col-1
        for j=2:row-1
            if (qtheta(i,j)==0)
                BW(i,j) = (magnitude(i,j)== max([magnitude(i,j),...
                    magnitude(i,j+1), magnitude(i,j-1)]));
            elseif (qtheta(i,j) == 1)
                BW(i,j) = (magnitude(i,j) == max([magnitude(i,j),...
                    magnitude(i+1,j-1), magnitude(i-1,j+1)]));
            elseif (qtheta(i,j) == 2)
                BW(i,j) = (magnitude(i,j) == max([magnitude(i,j),...
                    magnitude(i+1,j), magnitude(i-1,j)]));
            elseif (qtheta(i,j) == 3)
                BW(i,j) = (magnitude(i,j) == max([magnitude(i,j), ...
                    magnitude(i+1,j+1), magnitude(i-1,j-1)]));
            end
        end
    end
    
    BW = BW.*magnitude;
    
    
    T_min = 0.15;
    T_max = 0.35;
    T_min = T_min * max(max(BW));
    T_max = T_max * max(max(BW));
    edge_final = zeros (col, row);
    for i = 1  : col
        for j = 1 : row
            if (BW(i, j) < T_min)
                edge_final(i, j) = 0;
            elseif (BW(i, j) > T_max)
                edge_final(i, j) = 1;
            elseif ( BW(i+1,j)>T_max || BW(i-1,j)>T_max || BW(i,j+1)>T_max...
                    || BW(i,j-1)>T_max || BW(i-1, j-1)>T_max|| ...
                    BW(i-1, j+1)>T_max || BW(i+1, j+1)>T_max || BW(i+1, j-1)>T_max)
                edge_final(i,j) = 1;
            end
        end
    end
    img_canny = uint8(edge_final.*255);
    output_img = img_canny;
    % hough transform
    [H,T,R] = hough(output_img);
    P  = houghpeaks(H, 35,'threshold',ceil(0.1*max(H(:))));
    
    [lines] = houghlines(output_img,T,R,P,'FillGap',10,'MinLength',10);
    max_len = 0;
    
    c1 = [];
    c2 = [];
    l = [];
    for k = 1:length(lines)
        if(lines(k).theta < 75 && lines(k).theta > -75)
            c1 = [c1; [lines(k).point1 2]];
            c2 = [c2; [lines(k).point2 2]];
            l = [l;lines(k).point1 lines(k).point2];
        end
    end
    img_ori = insertShape(img_ori, 'Line', l);
    img_ori = insertShape(img_ori, 'Circle', c1);
    img_ori = insertShape(img_ori, 'Circle', c2);
    step(VideoOut, img_ori);
    step(VideoOut2, output_img);
end