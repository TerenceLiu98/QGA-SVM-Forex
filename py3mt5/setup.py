# coding:utf-8

from setuptools import setup
# or
# from distutils.core import setup  

setup(
        name='py3mt5',     
        version='0.1.0',   
        description='This is a enhanced python package for mt5 using MetaTrader5',  
        author='Terence Lau',  
        author_email='t_lau@uicstat.com',  
        url='https://github.com/TerenceLiu98/QGA-SVM-Forex',     
        packages= [''],
        install_requires = ['MetaTrader5', 'pandas'],
        classifiers = [
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',
        'License :: OSI Approved :: MIT License',
        	'Programming Language :: Python :: 3',
        	'Programming Language :: Python :: 3.3',
        	'Programming Language :: Python :: 3.4',
        	'Programming Language :: Python :: 3.5',
        	],
        python_requires='>=3'          
)