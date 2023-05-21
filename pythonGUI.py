#!/usr/bin/env python
# coding: utf-8

# In[20]:


import tkinter as tk
import webbrowser

def open_website_1():
    webbrowser.open('https://192.168.4.1/download')

def open_website_2():
    webbrowser.open('https://192.168.4.1/camer_health')

root = tk.Tk()
root.title("Camera Interface")
root.geometry("500x300")  # Set the window size to 500 pixels wide and 300 pixels high

# Add a border to the root window
root.configure(borderwidth=4, relief="solid")

header = tk.Label(root, text="Camera Interface", font=("Arial", 20, "bold"))
header.pack(pady=10)

wifi_label = tk.Label(root, text="Make sure you are connected to Wi-Fi\n\n\n name AccessPoint_CAM password : ******** ", font=("Arial", 10), fg="red")
wifi_label.pack()

button_frame = tk.Frame(root)
button_frame.pack()

# Add a border to the button frame
button_frame.configure(borderwidth=1, relief="solid")

# Set a background color for the buttons
button1 = tk.Button(button_frame, text="SYSTEM HEALTH", command=open_website_1, bg="lightgreen", fg="black")
button1.pack(side="left", padx=20)
button1.configure(relief="raised")
button2 = tk.Button(button_frame, text="DOWNLOAD FILES", command=open_website_2, bg="lightgreen", fg="black")
button2.pack(side="left", padx=20)

designed_by_label = tk.Label(root, text="Designed by Group7", font=("Arial", 10))
designed_by_label.pack(side="bottom", anchor="se", padx=10, pady=10)

root.mainloop()


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




