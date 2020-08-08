t = timer('TimerFcn', 'stat=false; thingSpeakWrite(800608,temp,"WriteKey","6QNS0D17I9FWIN17")',...
    'StartDelay',300);
stat=true;
start(t)
while (true)
    temp=10*randn(1)+50;
    while(stat==true)
        pause(1)
    end
    stat=true;
    disp("data upload");
    start(t)
end
