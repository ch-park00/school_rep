%%
fileID = fopen('rot_onoff.txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[3 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);
% motor off
fscanf(fileID,form2,sizeB);
data3=fscanf(fileID,formatSpec1,sizeA);
% direction changed
fscanf(fileID,form2,sizeC);
data4=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data5=fscanf(fileID,formatSpec1,sizeA);

% direction changed
fscanf(fileID,form2,sizeC);
data6=fscanf(fileID,formatSpec1,sizeA);
% direction changed
fscanf(fileID,form2,sizeC);
data7=fscanf(fileID,formatSpec1,sizeA);

% motor off
fscanf(fileID,form2,sizeB);
data8=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2 data3 data4 data5 data6 data7 data8];



figure();clf;
plot(data(1,:),data(3,:));hold on;grid on;
plot(data(1,:),data(2,:));
xlabel('Time');
ylabel('Motor Angle');
%plot(data(1,:),data(4,:))
%%
fileID = fopen('speed(p5).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);
%m motor off
fscanf(fileID,form2,sizeB);
data3=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2 data3];


figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:));axis([0 10 0 80]);
xlabel('Time');ylabel('Speed');
title('P=5,I=0,D=0');
%%
fileID = fopen('speed(p15).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);
fscanf(fileID,form2,sizeB);
data3=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2 data3];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:));axis([0 15 0 80]);
xlabel('Time');ylabel('Speed');
title('P=15,I=0,D=0');

%%
fileID = fopen('speed(p30).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);
fscanf(fileID,form2,sizeB);
data3=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2 data3];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:));axis([0 10 0 80]);
xlabel('Time');ylabel('Speed');
title('P=30,I=0,D=0');
%%
fileID = fopen('speed(p15,i20).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);
fscanf(fileID,form2,sizeB);
data3=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2 data3];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:));axis([0 10 0 80]);
xlabel('Time');ylabel('Speed');
title('P=15,I=20,D=0');
%%
fileID = fopen('speed(p15,i10).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);
fscanf(fileID,form2,sizeB);
data3=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2 data3];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:));axis([0 20 0 80]);
xlabel('Time');ylabel('Speed');
title('P=15,I=10,D=0');

%%
fileID = fopen('speed(p15,i20,d=0.0001).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);
fscanf(fileID,form2,sizeB);
data3=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2 data3];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:));axis([0 10 0 80]);
xlabel('Time');ylabel('Speed');
title('P=15,I=10,D=0.0001');


%%
fileID = fopen('speed(p15,i20,d=0.001).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);
fscanf(fileID,form2,sizeB);
data3=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2 data3];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:));axis([0 10 0 80]);
xlabel('Time');ylabel('Speed');
title('P=15,I=10,D=0.001');

%%
fileID = fopen('d(p5)_i.txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:))
xlabel('Time');ylabel('Angle');
title('P=5,I=0,D=0');

%%
fileID = fopen('d(p10)_i.txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:))
xlabel('Time');ylabel('Angle');
title('P=10,I=0,D=0');

%%
fileID = fopen('d(p15)_i.txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:))
xlabel('Time');ylabel('Angle');
title('P=15,I=0,D=0');

%%
fileID = fopen('d(p15,i1).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:))
xlabel('Time');ylabel('Angle');
title('P=15,I=1,D=0');
%%
fileID = fopen('d(p15,i3).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:))
xlabel('Time');ylabel('Angle');
title('P=15,I=3,D=0');

%%
fileID = fopen('d(p15,i3,d0.0001).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:))
xlabel('Time');ylabel('Angle');
title('P=15,I=3,D=0.0001');

%%
fileID = fopen('d(p15,i3,d0.002).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:))
xlabel('Time');ylabel('Angle');
title('P=15,I=3,D=0.002');
%%
fileID = fopen('d(p15,i3,d0.001).txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=9;
sizeC=18;
sizeA=[4 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);

data=[data1 data2];

figure();clf;
plot(data(1,:),data(3,:));hold on
plot(data(1,:),data(4,:))
xlabel('Time');ylabel('Angle');
title('P=15,I=3,D=0.001');

%%
fileID = fopen('step.txt','r');
formatSpec1 = '%f %f %f';
form2='%c';
sizeB=13;
sizeC=18;
sizeA=[3 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
fscanf(fileID,form2,sizeB);
data2=fscanf(fileID,formatSpec1,sizeA);
fscanf(fileID,form2,sizeC);
data3=fscanf(fileID,formatSpec1,sizeA);
data=[data1 data2 data3];

figure();clf;
plot(data(1,:),data(2,:));hold on;
plot(data(1,:),data(3,:));axis([0 60 0 100]);
xlabel('Time');ylabel('RPM');

%%
fileID = fopen('sync.txt','r');
formatSpec1 = '%f %f %f';
sizeA=[5 Inf];

% 초기 데이터
data1=fscanf(fileID,formatSpec1,sizeA);
% motor on
figure();clf;
plot(data1(1,:),data1(2,:));hold on;
plot(data1(1,:),data1(3,:));
xlabel('Time');ylabel('step angle');
figure();clf;
plot(data1(1,:),-data1(4,:));hold on;
plot(data1(1,:),-data1(5,:));
xlabel('Time');ylabel('servo angle');