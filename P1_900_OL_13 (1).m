%{
Project 1 from 
Khang Nguyen and Somil Ajmera ENGR 1250-900 11/07/2020
Team nnumber- 900_OL_13
 %}

clear
clc
close all

% Creating a cell array to put in values in from the table of material cost
all_costs = {'Concrete', 16, 30, 96000, 900, 5, 5; 'Wood', 23, 53, 115000, 800, 12, 11; 'Adobe', 18, 42, 68000, 600, 6, 5};

% Fixed cost calculation
choice = menu('Select material', all_costs(1,1), all_costs(2,1), all_costs(3,1));
desired_cost = all_costs(choice,:);
fixed_cost = 3000*desired_cost{2}/12*desired_cost{3} + desired_cost{4} + desired_cost{5}*desired_cost{6}*desired_cost{7};

% Asking user inputs to calculate Variable cost and Renvenue
energy = input('Energy Cost [$/week]: ');
labor = input('Labor Cost [$/week]: ');
maintenance = input('Maintenance Cost [$/week]: ');
landfill = input('Landfill Cost [$/week]: ');
weeks_per_year = input('Number of weeks per year the zoo will operate: ');
years = input('Number of years for analysis: '); 
ticket_price = input('Admission Price [$/person]: ');
ppl = input('Number of People per week that will visit the zoo: ');
donations = input('Expected donations per week [$/week]: ');

% Breakeven caluculations and specific calculations asked in the project 
variable_cost = energy + labor + maintenance + landfill;
year_cost = variable_cost*weeks_per_year;
cost_vector = fixed_cost : year_cost : (years*year_cost + fixed_cost);
year_revenue = (ticket_price*ppl + donations)*weeks_per_year;
revenue_vector = 0 : year_revenue : years*year_revenue;
profit_vector = revenue_vector - cost_vector;
break_time = 12*fixed_cost/(year_revenue - year_cost);
donations_needed = (fixed_cost + 28*variable_cost) - 28*(ticket_price*ppl + donations);

% Printing the result summary
fprintf("-----------------------------------------------------------------------------\n");
fprintf("\t\t\t\t\t\t\tRESULT SUMMARY\n");
fprintf("-----------------------------------------------------------------------------\n");
fprintf("Material: %s\n", all_costs{choice});
fprintf("\tOperating %d weeks per year will generate per year: \n", weeks_per_year);
fprintf("\t\tRevenue: \t$%d\n", year_revenue);
fprintf("\t\tCost: \t\t$%d\n", year_cost);
fprintf("\tThe breakeven time is %.2f months.\n", break_time);
fprintf("\tThe total profit after %d years is $%.3e.\n", years, profit_vector(years + 1));
fprintf("-----------------------------------------------------------------------------\n");
fprintf("It will take a one-time donation of $%.2f to breakeven in seven months.\n", donations_needed);
fprintf("-----------------------------------------------------------------------------\n");

%ploting of the graph of revenue and total cost against time 
figure(1)
t = [0:0.5:years];
revenue = t*year_revenue;
cost = t*year_cost + fixed_cost;
axis([0 years 0 revenue_vector(years + 1)]);
plot(t, revenue, 'r', t, cost, 'b');
hold on;
plot(break_time/12, (break_time/12)*year_revenue, 'r.', 'MarkerSize', 35);
grid on;
title('Cost and Revenue of the zoo over Analysis Time');
xlabel('Time (t) [yr]');
ylabel('Cost (C) [$] or Revenue (R) [$]');
labels = {'Revenue', 'Cost'};
legend(labels, 'Location', 'northwest');

%the additional plot of profit against time
figure(2)
t = [0:0.5:years];
profit = t*year_revenue - (t*year_cost + fixed_cost);
axis([0 years profit_vector(1) profit_vector(years + 1)]);
plot(t, profit);
hold on;
plot(break_time/12, (break_time/12*year_revenue-(break_time/12*year_cost+fixed_cost)), 'r.', 'MarkerSize', 35);
grid on;
title('Profit of the zoo over Analysis Time');
xlabel('Time (t) [yr]');
ylabel('Profit (P) [$]');
labels = {'Profit'};
legend(labels, 'Location', 'northwest');

