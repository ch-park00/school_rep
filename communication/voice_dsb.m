%% 변조
[s,Fs]=audioread('hello.mp4');
sound(s,Fs);
N=length(s);
t=(0:N-1)*(1/Fs);
figure(1),plot(t,s);xlabel('time $t$(sec)','Interpreter','Latex')
figure(2),spectrogram(s(:,1),256,128,256,Fs,'yaxis');
pause(5)

x=s.*cos(2*pi*8000*t');
sound(x,Fs);
figure(3),plot(t,x);xlabel('time $t$(sec)','Interpreter','Latex')
figure(4),spectrogram(x(:,1),256,128,256,Fs,'yaxis')
pause(5)

%% 복조
m=2*x.*cos(2*pi*8000*t');
m1=filter(h,1,m);
sound(m1,Fs);

figure(5),plot(t,m);xlabel('time $t$(sec)','Interpreter','Latex')
figure(6),spectrogram(m(:,1),256,128,256,Fs,'yaxis');
figure(7),plot(t,m1);xlabel('time $t$(sec)','Interpreter','Latex')
figure(8),spectrogram(m1(:,1),256,128,256,Fs,'yaxis');
