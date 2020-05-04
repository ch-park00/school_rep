%%
th=0:0.01*pi:2*pi;
x=2*cos(th);y=2*sin(th);
th1=pi/4:0.1*pi:11/18*pi;
x1=[2*cos(11/18*pi) -1.2 -1.45 -1.3 -0.6 0 1 1.75...
    2.75 3.5 4.4 5.1 6.1 7.8 8 7.8 4.5 3.5 2.5 1.7 2*cos(pi/4) 2*cos(th1);...
    2*sin(11/18*pi) 3.3 5 6 7.5 8.1 8.5 8.55 8.4 8 ...
7.5 6.85 6 4.3 4 3.7 3.8 3.7 3.3 2.2 2*sin(pi/4) 2*sin(th1)];
x2=[cos(2/3*pi) sin(2/3*pi);-sin(2/3*pi) cos(2/3*pi)]*x1;
x3=[cos(2/3*pi) sin(2/3*pi);-sin(2/3*pi) cos(2/3*pi)]*x2;

%% plot ±×¸®±â
figure(1);pause(1)
for i=1:5
    cnt=1;
    k=0.03*pi*i; % È¸Àü¼Óµµ Á¶Àý
    tic
for th2=2*pi:-k:0.1*pi %cw Ãà¼Ò
   temp=[cos(th2) -sin(th2);sin(th2) cos(th2)];
   y1=(th2/(2*pi))*temp*x1;
   y2=(th2/(2*pi))*temp*x2;
   y3=(th2/(2*pi))*temp*x3;
   clf;
   fill((th2/(2*pi))*x,(th2/(2*pi))*y,'b')
   hold on;grid on;axis([-15 15 -15 15])
   fill(y1(1,:),y1(2,:),[0.3 0.3 0.3])
   fill(y2(1,:),y2(2,:),[0.3 0.3 0.3])
   fill(y3(1,:),y3(2,:),[0.3 0.3 0.3])
   text(-5,13,'201401653 ¹ÚÃ¶Èñ','fontsize',15)
   if cnt<5
     cnt=cnt+1;
   elseif cnt==5 
     time1=toc;
     t1=((k*cnt)/(2*pi));
     rpm1=t1*60/time1;
     cnt=cnt+1;
   else
     text(-5,-13,['rpm : ' num2str(rpm1)],'fontsize',15);
   end
   pause(0.0001)
end
cnt=1;
tic
for th2=0.1*pi:k:2*pi %ccw È®´ë
   temp=[cos(th2) -sin(th2);sin(th2) cos(th2)];
   y1=(th2/(2*pi))*temp*x1;
   y2=(th2/(2*pi))*temp*x2;
   y3=(th2/(2*pi))*temp*x3;
   clf;fill((th2/(2*pi))*x,(th2/(2*pi))*y,'b')
   hold on;grid on;axis([-15 15 -15 15])
   fill(y1(1,:),y1(2,:),[0.3 0.3 0.3])
   fill(y2(1,:),y2(2,:),[0.3 0.3 0.3])
   fill(y3(1,:),y3(2,:),[0.3 0.3 0.3])
   text(-5,13,'201401653 ¹ÚÃ¶Èñ','fontsize',15)
   if cnt<5
     cnt=cnt+1;
   elseif cnt==5 
     time1=toc;
     t1=((cnt*k)/(2*pi));
     rpm2=t1*60/time1;
     cnt=cnt+1;
   else
     text(-5,-13,['rpm : ' num2str(rpm2)],'fontsize',15);
   end
   pause(0.0001)
end
end