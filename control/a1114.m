%%
w=0:0.01:100;
G=20./(4*w*1i+1);
figure(1);clf;
subplot(211),semilogx(w,20*log10(abs(G)));
subplot(212),semilogx(w,unwrap(angle((G)))*(180/pi));
%%

% G(jw) = Wn^2/(2*zeta*Wn*w+(Wn^2-w^2))
w=0:0.01:200;
zeta=0.1;
G=1./(1i*2*zeta*1*w + (1-(w.^2)));
figure(1);clf;
subplot(211),semilogx(w,20*log10(abs(G)));xlabel('\omega (rad/sec)');ylabel('Gain(dB)');xlim([0.1 100]);ylim([-40 20]);grid on;
subplot(212),semilogx(w,unwrap(angle((G)))*(180/pi));xlabel('\omega (rad/sec)');ylabel('Phase(deg)');xlim([0.1 100]);ylim([-200 20]);grid on;
