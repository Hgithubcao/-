-- 剔除重复的数据
select distinct * from Supplement

delete from Supplement 
where (name) in (select name from Supplement group by name having count(*) > 1)
and rowid not in (select min(rowid) from Supplement group by name having count(*)>1) 