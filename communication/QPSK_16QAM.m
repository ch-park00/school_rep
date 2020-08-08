EbNodBs=0:2:10;
N=length(EbNodBs);
run('hw1115');
for n=1:N
    EdB=EbNodBs(n);
    sim('hw1115.slx');
    ber(n)=data1.Data(2);
    ber1(n)=data2.Data(2);
end
figure(1);axis([-1 11 0 10^5]);
semilogy(EbNodBs,ber,'ro-');
hold on;
semilogy(EbNodBs,ber1,'bo-');
xlabel('SNR');ylabel('Error');
legend('QPSK','16-QAM')