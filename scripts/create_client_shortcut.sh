root_proj=$HOME/dek-soldiers
shortcut_file=$root_proj/shortcut/client.desktop
icon_file=$root_proj/image/client_icon.png
desktop_file=$HOME/Desktop/client.desktop
 
sed -e "s,Icon=.*,Icon=$icon_file,g" -i $shortcut_file
ln -s $shortcut_file -f $desktop_file