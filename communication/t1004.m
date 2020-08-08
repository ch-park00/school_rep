T = 2; %전체구간
Fs = 1e5; Ts = 1/Fs;
t = -T/2:Ts:T/2; %신호가 있는 구간
t1=-2:Ts:T;
x = [zeros(1,Fs) 100*cos(2*pi*0.25*t) zeros(1,Fs)]; 
figure(1); plot( t1, x, 'LineWidth', 2 );
grid on; xlim([-2 2]);
set( gca, 'XTick', [-2:0.5:2]);
xlabel('time $t$ (sec)', 'Interpreter', 'latex');

fd = 10;
N  =  length(x);
X  = fft(x, N)*Ts;
Xc = fftshift(X);
XcdB = 20*log10(abs(Xc));
f  = Fs/2*([0:N-1]-N/2)/N;
figure(2); plot( f, XcdB-max(XcdB), 'LineWidth', 2 );
grid on; xlim(5e3*[-1 1]); ylim([-100 0]);
xlabel('frequency $f$ (Hz)', 'Interpreter', 'latex');
ylabel('normalized power (dB)');
