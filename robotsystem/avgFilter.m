function avg=avgFilter(x)

persistent prevAvg k
persistent firstrun

if isempty(firstrun)
    k=1;
    prevAvg=0;
    
    firstrun=1;
end

alpha=(k-1)/k;
avg=alpha*prevAvg+(1-alpha)*x;

prevAvg=avg;
k=k+1;

