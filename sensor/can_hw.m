%% 
panel=imread('Panel1_fix.jpg'); % 계기판 패널 이미지
point=imread('point_fix.jpg'); % 계기판 바늘 이미지
handle=imread('handle.jpg'); % 핸들 이미지

load temp.txt; % can 데이터 불러오기
rpmdata=temp(:,2); % can data 중 RPM에 대한 데이터
rot_point=round(-0.03*rpmdata); % RPM 바늘 각도 계산 
d_len=length(rot_point);
figure()
for i=1:9:d_len % 동영상과 싱크 조정
    point2=imrotate(point,rot_point(i,1)); % 계기판 RPM에 맞게 회전
    handle2=imrotate(handle,temp(i,1)); % 핸들 회전
    len_pt2=round(length(point2)/2);
    len=round(length(handle2)/2);
   if len_pt2~=300 % 이미지 크기 조정
      point2=point2(len_pt2-299:len_pt2+300,len_pt2-299:len_pt2+300,:);
   end
   if len~=125 % 이미지 크기 조정
       handle2=handle2(len-124:len+125,len-124:len+125,:);
   end
    final=point2+panel; % 바늘과 계기판 합성
    subplot(211);imshow(final);
    subplot(212);imshow(handle2);
    pause(0.01);
end