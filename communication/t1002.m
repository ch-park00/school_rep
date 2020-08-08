%%
Fs = 1000; Ts = 1/Fs;
t  = -5:Ts:5;
x1 = rect(t, 1.0);
x2 = rect(t, 0.2);
figure(1); plot(t, x1, t, x2, 'LineWidth', 1); grid on;
xlabel('time $t$ (sec)', 'Interpreter', 'latex');
axis([-2 2 0 1.2]);
N = length(t);
X1 = fft(x1) * Ts; X1a = abs(fftshift(X1));
X2 = fft(x2) * Ts; X2a = abs(fftshift(X2));
f = Fs*(-N/2:N/2-1)/N;
figure(2); plot(f, X1a, f, X2a, 'LineWidth', 1); grid on;
xlabel('frequency $f$ (Hz)', 'Interpreter', 'latex');
xlim( 10*[-1 1] );

%% Time domain waveform
T = 1e-3; % pulse duration
Fs = 1e5; Ts = 1/Fs; %최소 원래 주파수보다 100배이상빨라야한다.
t = -T/2:Ts:T/2;
x = 0.5*(cos(2*pi*t/T)+1);
figure(1); plot( t, x, 'LineWidth', 2 );
grid on; xlim(1.0e-3*[-1 1]);
set( gca, 'XTick', 1e-3*[-1:0.5:1]);
xlabel('time $t$ (sec)', 'Interpreter', 'latex');
%% Frequency domain spectrum
fd = 10; % frequency resolution
N  = 2^(nextpow2(ceil(Fs/fd))); %%N을 2의 제곱수로 만드는 이유는 속도가 가장 빠르기 때문
X  = fft(x, N)*Ts;
Xc = fftshift(X);
XcdB = 20*log10(abs(Xc));
f  = Fs/2*([0:N-1]-N/2)/N;
figure(2); plot( f, XcdB-max(XcdB), 'LineWidth', 2 );
grid on; xlim(5e3*[-1 1]); ylim([-100 0]);
xlabel('frequency $f$ (Hz)', 'Interpreter', 'latex');
ylabel('normalized power (dB)');

%% 미션
T = 4e-3;
Fs = 4e5; Ts = 1/Fs;
t = -T/2:Ts:T/2;
x = [linspace(0,2,length(t)/2) linspace(2,0,length(t)/2+1)];
figure(1); plot( t, x, 'LineWidth', 2 );
grid on; xlim(1.0e-3*[-2 2]);
set( gca, 'XTick', 1e-3*[-2:0.5:2]);
xlabel('time $t$ (sec)', 'Interpreter', 'latex');

fd = 10;
N  = 2^(nextpow2(ceil(Fs/fd)));
X  = fft(x, N)*Ts;
Xc = fftshift(X);
XcdB = 20*log10(abs(Xc));
f  = Fs/2*([0:N-1]-N/2)/N;
figure(2); plot( f, XcdB-max(XcdB), 'LineWidth', 2 );
grid on; xlim(5e3*[-1 1]); ylim([-100 0]);
xlabel('frequency $f$ (Hz)', 'Interpreter', 'latex');
ylabel('normalized power (dB)');
