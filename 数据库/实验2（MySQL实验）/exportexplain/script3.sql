use employees;
EXPLAIN SELECT E.emp_no, CONCAT(first_name, ' ',last_name), from_date, to_date, salary
FROM employees E, salaries S
WHERE E.emp_no=S.emp_no
ORDER BY E.emp_no, from_date
