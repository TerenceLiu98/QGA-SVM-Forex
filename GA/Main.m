%% Genetic Algorithm in MATLAB %% 
%  Author: Terence Liu (UIC)    %

N = 100;% number of individuals in the population
N_chrom = 2;% number of chromosome nodes
iter = 2000;% iterations
mut = 0.2;% mutation probability
acr = 0.2;% crossover probability

chrom_range = [-10 -10; 10 10];% the interval of each node's value
chrom = zeros (N, N_chrom);% matrix for storing chromosomes
fitness = zeros (N, 1);% fitness of stored chromosomes
fitness_ave = zeros (1, iter);% stores the average fitness of each generation
fitness_best = zeros (1, iter);% stores the optimal fitness of each generation
chrom_best = zeros (1, N_chrom + 1);% stores the optimal chromosome and fitness of the current generation

chrom = Initialize(N, N_chrom, chrom_range); % initilize the chrom
fitness = CalFitness(chrom, N, N_chrom); % calculuate fitness
chrom_best = FindBest(chrom, fitness, N_chrom); % find the best chrom
fitness_best(1) = chrom_best(end); % store the best chrom into a matrix
fitness_ave(1) = CalAveFitness(fitness); % store the avg fitness into a matrix


for t = 2:iter
    chrom = MutChrom(chrom, mut, N, N_chrom, chrom_range, t, iter); % variation 
    chrom = AcrChrom(chrom, acr, N, N_chrom); % crossover
    fitness = CalFitness(chrom, N, N_chrom); % calculate fittness 
    chrom_best_temp = FindBest(chrom, fitness, N_chrom); %find the best chrom
    if chrom_best_temp(end)>chrom_best(end) % replace the last 'best'
        chrom_best = chrom_best_temp;
    end
   
    [chrom, fitness] = ReplaceWorse(chrom, chrom_best, fitness);
    fitness_best(t) = chrom_best(end); % store the best chrom into a matrix
    fitness_ave(t) = CalAveFitness(fitness); % store the avg fitness into a matrix
end

%%??
figure(1)
plot(1:iter, fitness_ave, 'r', 1:iter, fitness_best, 'b')
grid on
legend('?????', '?????')
e = PlotModel(chrom_best)

%%????
disp(['The best chrom is', num2str(chrom_best(1:end-1))])
disp(['The best fitness is', num2str(chrom_best(end))])

