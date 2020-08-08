%%
[s Fs]=audioread('music_1.mp3');
x=[s(Fs*200:Fs*210-1,1) s(Fs*200:Fs*210-1,2)];
t=linspace(0,10,length(x));
figure(1),plot(t,x(:,1),'r');xlabel('time $t$ (sec)','Interpreter','Latex');
title('waveform')
y=filter(h,1,x);
figure(2),plot(t,y(:,1),'b')
xlabel('time $t$ (sec)','Interpreter','Latex');
title('waveform')
%%
fd = 10; % frequency resolution
N = 2^(nextpow2(ceil(Fs/fd))); 
X=fft(x(:,1),N)*(1/Fs);
X=fftshift(X);
XcdB = 20*log10(abs(X));
f  = Fs*([0:N-1]-N/2)/N;
figure(3); plot( f, XcdB-max(XcdB),'r', 'LineWidth', 2 );
grid on; xlim(6e3*[-1 1]); ylim([-100 0]);
xlabel('frequency $f$ (Hz)', 'Interpreter', 'latex');
ylabel('normalized power (dB)');

Y=fft(y(:,1),N)*(1/Fs);
Y=fftshift(Y);
YcdB=20*log10(abs(Y));
f  = Fs*([0:N-1]-N/2)/N;
figure(4); plot(f,YcdB-max(YcdB),'b', 'LineWidth', 2 );
grid on; xlim(6e3*[-1 1]); ylim([-100 0]);
xlabel('frequency $f$ (Hz)', 'Interpreter', 'latex');
ylabel('normalized power (dB)');
sound(x(:,1),Fs);pause(11)
sound(y,Fs)