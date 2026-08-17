

#ver todos los tags completo 
git --no-pager tag

#ultimo tag
git describe --tags --abbrev=0


#ultimo tag otro cmd 
git tag | tail -1


#todos los push si tienen tag
git ls-remote --tags origin


git log --oneline --decorate --tags
#push por fecha 
#git log --oneline --format="%h %ad %s" --date=format:"%Y-%m-%d %H:%M:%S"
git --no-pager log --tags --simplify-by-decoration --oneline --format="%h %ad %s" --date=format:"%Y-%m-%d %H:%M:%S"
git --no-pager log origin/main --oneline --format="%h %ad %s" --date=format:"%Y-%m-%d %H:%M:%S"



#
