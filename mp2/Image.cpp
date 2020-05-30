#include "Image.h"
namespace cs225{
	void Image::lighten(double amount){
		HSLAPixel* pixel;
		for(unsigned int i=0; i<this->height();i++){
			for(unsigned int j=0;j<this->width();j++){
				pixel = this->getPixel(j,i);
				pixel->l+=amount;
				if(pixel->l >1){
					pixel->l=1;
				}
			}
		}
	}
	void Image::lighten(){
		this->lighten(0.1);
	}
	void Image::darken(){
		this->darken(0.1);
	}
	void Image::darken(double amount){
		HSLAPixel* pixel;
		for(unsigned int i=0; i<this->height();i++){
			for(unsigned int j=0;j<this->width();j++){
				pixel = this->getPixel(j,i);
				pixel->l-=amount;
				if(pixel->l < 0){
					pixel->l=0;
				}
			}
		}
	}
	void Image::saturate(){
		this->saturate(0.1);
	}
	void Image::saturate(double amount){
		HSLAPixel* pixel;
		for(unsigned int i=0; i<this->height();i++){
			for(unsigned int j=0;j<this->width();j++){
				pixel = this->getPixel(j,i);
				pixel->s += amount;
				if(pixel->s > 1){
					pixel->l=1;
				}
			}
		}
	}
	void Image::desaturate(){
		this->desaturate(0.1);
	}
	void Image::desaturate(double amount){
		HSLAPixel* pixel;
		for(unsigned int i=0; i<this->height();i++){
			for(unsigned int j=0;j<this->width();j++){
				pixel = this->getPixel(j,i);
				pixel->s-=amount;
				if(pixel->s < 0){
					pixel->s=0;
				}
			}
		}
	}
	void Image::illinify(){
		for(unsigned int x=0; x<this->width(); x++){
			for(unsigned int y=0; y<this->height(); y++){
			      HSLAPixel *pixel = this->getPixel(x, y);
			      double OGhue=pixel->h;
			      if((OGhue < 102.5) || (OGhue > 293.5)){
				      pixel->h=11.0;
			      }else{
				      pixel->h=216.0;
			      }
			}
		}
	}
	void Image::grayscale(){
		for(unsigned int x=0; x<this->width();x++){
			for(unsigned int y=0; y<this->height(); y++){
				HSLAPixel* pixel = this->getPixel(x,y);
				pixel->s = 0;
			}
		}
	}
	void Image::rotateColor(double degrees){
		for(unsigned int x=0; x<this->width();x++){
			for(unsigned int y=0; y<this->height(); y++){
				HSLAPixel* pixel = this->getPixel(x,y);
				pixel->h += degrees;
				if(pixel->h > 360){
					pixel->h -= 360;
				}
				if(pixel->h < 0){
					pixel->h += 360;
				}
			}
		}
	}
	void Image::scale(double factor){
		Image copy = *this;
		this->resize(this->width()*factor,this->height()*factor);
		for(unsigned int x=0;x<this->width();x++){
			for(unsigned int y=0;y<this->height();y++){
				HSLAPixel* pixel=this->getPixel(x,y);
				HSLAPixel *Cpixel = copy.getPixel(x/factor,y/factor);
				pixel->h=Cpixel->h;
				pixel->s=Cpixel->s;
				pixel->l=Cpixel->l;
				pixel->a=Cpixel->a;

			}
		}
	}
	void Image::scale(unsigned w, unsigned h){
		double factor;
		if((double)w/this->width() < (double)h/this->height() ){
			factor = (double)w/this->width();
		}else{factor = (double)h/this->height();}
		this->scale(factor);
	}
}
