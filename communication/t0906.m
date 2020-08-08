t=linspace(0,0.03,100);
s=cos(200*pi*t);
s_i=0.2*sin(600*pi*t+(pi/12));
r=s+s_i;
plot(t,s,'b');
hold on;grid on;
plot(t,s_i,'r');
plot(t,r,'k','Linewidth',2);
xlabel('time $t$(sec)','Interpreter','latex'); % $와 $ 사이에 있는 것은 수식으로 변한다.(Latex)
text(0.015,1.4,'$s(t)=0.2*\cos(200\pi*t)$', 'Interpreter', 'latex','color','b'); 
text(0.015,1.2,'$s_i(t)=0.2*\sin(600\pi*t+\pi/12)$', 'Interpreter', 'latex','color','r');
text(0.001,1.3,'201401653 박철희');