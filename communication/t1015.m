%% 
Fs  = 1000; Ts = 1/Fs;
t   = (0:Ts:2);
m   = sin(2*pi*t); % 보내는 신호
xpm = cos(2*pi*10*t + 5*m); %PM
xfm = cos(2*pi*10*t + 20*cumtrapz(m)*Ts); %FM
% cumtrapz : 사다리꼴로 적분 cumsum도 쓸 수 있지만 cumtrapz가 더 정확
% fm 적분계수가 20인 이유는 FM설계시 주파수 범위가 +-100MHz범위를 넘지 않게 하기 위함
figure(1); plot( t, m ); hold on; 
plot(t, xpm, 'LineWidth', 2);
hold off; axis off;
figure(2); plot( t, m ); hold on; 
plot(t, xfm, 'LineWidth', 2);
hold off; axis off;

%%
Fs  = 1000; Ts = 1/Fs;
t   = (0:Ts:20);
m   = sin(2*pi*0.1*t); %1/10Hz
x   = cos(2*pi*200*t + 500*m); %PM
figure(1);
spectrogram(x, 256, 128, 256, Fs, 'yaxis' );
fi  = 200 + 50*cos(0.2*pi*t);
figure(2);
plot( t, fi, 'LineWidth', 2 ); grid on;
xlabel('time $t$ (sec)', 'Interpreter', 'latex');
ylabel('frequency $f_i$ (Hz)', 'Interpreter', 'latex');
ylim([0 500]);

%%
t1=linspace(-0.05,0,10000);
t2=linspace(0,0.05,10000);
y=cos(200*pi*t1);
y1=cos(300*pi*t2);
t=[t1 t2];
x=[y y1];
plot(t,x)
xlabel('time $t$ (sec)','Interpreter','Latex');
ylabel('frequency $f$ (Hz)','Interpreter','Latex')