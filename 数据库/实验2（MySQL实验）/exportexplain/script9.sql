use employees;
EXPLAIN SELECT E.emp_no, CONCAT(first_name, ' ',last_name), from_date, to_date, MAX(salary)
FROM salaries S, employees E
WHERE S.emp_no=E.emp_no 
GROUP BY E.emp_no
ORDER BY E.emp_no
