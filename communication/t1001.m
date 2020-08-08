%%
t=linspace(0,4e-3,2000);
f0=1e6;
s=cos(2*pi*f0*t)-(0.2*cos(2*pi*3*f0*t));
plot(t,s);
grid on;
xlabel('time $t$ (sec)','Interpreter','Latex');

%%
N = 8;
x = [0 0 1 1 1 1 0 0];
X = fft(x)/N;
fftshift(0:7);
figure(1);
stem(0:N-1, abs(X),'fill'); 
grid on;

%%
fftshift([7 9 1 0 2 4 5 3])

%% 집에서 해보기
N = 256;
xn = [ones(64,1); zeros(128,1); ...
    ones(64,1)];
Xk = fft(xn) / N;
t = -4:0.01:4;
figure(1); %세로축은 크기를 의미하는데, 보통 제곱해서 dBm으로 표시하는 경우가 많다
n = -128:127;
stem(n, fftshift(abs(Xk)),'fill'); %abs의 의미는 복소수의 크기를 의미
grid on;

s = Xk(1);
for k=2:10
  s = s + Xk(k)*exp(2i*pi*(k-1)*t) ...
      + Xk(N-k+2)*exp(-2i*pi*(k-1)*t);
end
figure(2);
plot(t, s); grid on;
