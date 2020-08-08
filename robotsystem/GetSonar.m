function h=GetSonar()

persistent sonarAlt
persistent k firstrun

if isempty(firstrun)
    load SonarAlt
    k=1;
    firstrun=1;
end
h=sonarAlt(k);

k=k+1;