%여기에는 실시간 병상정보를 조회한다.
data=webread...
    ("http://apis.data.go.kr/B552657/ErmctInfoInqireService/getEmrrmRltmUsefulSckbdInfoInqire?serviceKey=ltZzQq2Ww17UOf%2Bu4%2BWwRzkGJIUdVqYo%2BwN38qVhOEk9JDmIOlNHDnkP7I%2BjDtXiX%2Bm3j5cOkzF8o4Y6yBIoxQ%3D%3D&numOfRows=401");
%좌표랑 이름이랑 저장되어있음
data1=webread("http://apis.data.go.kr/B552657/ErmctInfoInqireService/getEgytListInfoInqire?serviceKey=ltZzQq2Ww17UOf%2Bu4%2BWwRzkGJIUdVqYo%2BwN38qVhOEk9JDmIOlNHDnkP7I%2BjDtXiX%2Bm3j5cOkzF8o4Y6yBIoxQ%3D%3D&numOfRows=401");
% 중증질환자 수용가능 여부 확인
data2=webread("http://apis.data.go.kr/B552657/ErmctInfoInqireService/getSrsillDissAceptncPosblInfoInqire?servicekey=ltZzQq2Ww17UOf%2Bu4%2BWwRzkGJIUdVqYo%2BwN38qVhOEk9JDmIOlNHDnkP7I%2BjDtXiX%2Bm3j5cOkzF8o4Y6yBIoxQ%3D%3D&numOfRows=401");
%%
%하나씩 매칭되는 거 있음.확인완료
for i=1:401
    for j=1:318
   if strcmp(data.response.body.items.item{i,1}.dutyName,data2.response.body.items.item(j,1).dutyName)==1
       new_data{i,1}=data2.response.body.items.item(j,1);
   end
    end
    for j=1:401
   if strcmp(data.response.body.items.item{i,1}.hpid,data1.response.body.items.item{j,1}.hpid)==1
       new_data1{i,1}=data1.response.body.items.item{j,1};
   end
    end
end

%%
    api = 'https://maps.googleapis.com/maps/api/';
    url = [api 'geocode/json?address=논현로235' ...
        '&key=AIzaSyDpgBOWLjCw4sZI3I9q3xU8jPNttyUSkQ4'];
   answer= webread(url);
   
%%
place='의정부시';
api = 'https://maps.googleapis.com/maps/api/';
url = [api 'geocode/json?address=' place ...
        '&key=AIzaSyDpgBOWLjCw4sZI3I9q3xU8jPNttyUSkQ4'];
answer= webread(url);
%%
lat=answer.results.geometry.location.lat;
lng=answer.results.geometry.location.lng;

idx=0;
min=9999;
for i=1:401
    if ischar(new_data1{i,1}.wgs84Lat)==1
       temp(i,1)=str2double(new_data1{i,1}.wgs84Lat); 
    else
        temp(i,1)=new_data1{i,1}.wgs84Lat;
    end
    if ischar(new_data1{i,1}.wgs84Lon)==1
        temp1(i,1)=str2double(new_data1{i,1}.wgs84Lon);
    else
        temp1(i,1)=new_data1{i, 1}.wgs84Lon;
    end
    
end
idx=0;
min=999;
for i=1:401
    latdist=abs(lat-temp(i,1));
    lngdist=abs(lng-temp1(i,1));
    if min>latdist^2+lngdist^2
        min=latdist^2+lngdist^2;
        idx=i;
    end
end
%%