EbNodBs=0:2:10;
N=length(EbNodBs);
run('QPSK_sim');
for n=1:N
    Edb=EbNodBs(n);
    sim('QPSK_sim.slx');
    ber(n)=BERs.Data(2);
end
semilogy(EbNodBs,ber,'ro');