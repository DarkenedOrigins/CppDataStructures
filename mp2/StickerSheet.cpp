#include "StickerSheet.h"
using namespace cs225;
namespace cs225{
	StickerSheet::StickerSheet(const Image &picture, unsigned max){
		max_=max;
		count_=0;
		BaseImage_ = new Image(picture);
		head = NULL;
	}
	StickerSheet::~StickerSheet(){
		Sticker* temp;
		for(unsigned i=0;i<count_;i++){
			temp = head->next;
			delete head->image;
			delete head;
			head =temp;
		}
		delete BaseImage_;
	}
	StickerSheet::StickerSheet(const StickerSheet &other){
		max_=other.max_;
		count_=other.count_;
		BaseImage_= new Image( *(other.BaseImage_) );
		if(count_<1){head=NULL; return;}

		Image *tempImg = new Image( *(other.head->image) );
		head = new Sticker(tempImg, other.head->x, other.head->y);
		Sticker* temp = head;
		Sticker* othertemp = other.head->next;
		for(unsigned i=1; i < count_; i++){
			tempImg = new Image( *(othertemp->image) );
			temp->next = new Sticker(tempImg, othertemp->x, othertemp->y);
			temp = temp->next;
			othertemp = othertemp->next;
		}
	}
	const StickerSheet& StickerSheet::operator= (const StickerSheet &other){
		this->max_=other.max_;
		this->count_=other.count_;
		this->BaseImage_= new Image( *(other.BaseImage_) );
		if(count_<1){head=NULL; return *this;}

		Image *tempImg = new Image( *(other.head->image) );
		this->head = new Sticker(tempImg, other.head->x, other.head->y);
		Sticker* temp = this->head;
		Sticker* othertemp = other.head->next;
		for(unsigned i=1; i < count_; i++){
			tempImg = new Image( *(othertemp->image) );
			temp->next = new Sticker(tempImg, othertemp->x, othertemp->y);
			temp = temp->next;
			othertemp = othertemp->next;
		}
		return *this;
	}
	void StickerSheet::changeMaxStickers (unsigned max){
		if(max >= max_){
			max_=max;
			return;
		}
		if(max >= count_){
			max_=max;
			return;
		}
		Sticker* ptr=head;
		for(unsigned i=0; i<max; i++){
			ptr=ptr->next;
		}
		Sticker* temp; 
		while(ptr != NULL){
			temp = ptr;
			ptr=ptr->next;
			delete temp->image;
			delete temp;
		}
		max_=max;
		count_=max;
		return;
	}
	int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
		if(count_ == max_){return -1;}
		Sticker* temp=head;	
		Image* stickerptr= new Image(sticker);
		if(count_==0){
			head = new Sticker(stickerptr,x,y);
			count_++;
			return 0;
		}
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = new Sticker(stickerptr,x,y);
		count_++;
		return count_-1;
	}
	bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
		if(index >= count_){return false;}
		Sticker* node = head;
		for(unsigned i=0; i<index; i++){
			node = node->next;
		}
		node->x = x;
		node->y = y;
		return true;
	}
	void StickerSheet::removeSticker(unsigned index){
		if(index >= count_ ){return;}
		Sticker* node = head;
		Sticker* prevnode = NULL;
		if(index == 0){
			head = head->next;
			delete node->image;
			delete node;
			count_--;
			return;
		}
		for(unsigned i=0; i<index; i++){
			prevnode = node;
			node = node->next;
		}
		prevnode->next = node->next;
		delete node->image;
		delete node;
		count_--;
		return;
	}
	Image* StickerSheet::getSticker(unsigned index) const{
		if(index >= count_){return NULL;}
		Sticker* node = head;
		for(unsigned i=0; i<index; i++){
			node = node->next;
		}
		return node->image;
	}
	Image StickerSheet::render() const{
		Sticker* StickerNode = head;
		for(unsigned i=0; i<count_; i++){
			double BaseWidth = BaseImage_->width();
			unsigned Xcoord= StickerNode->x;
			double StickerWidth = StickerNode->image->width();
			if(StickerWidth+Xcoord > BaseWidth){
				double factor = (StickerWidth+Xcoord)/BaseWidth;
				BaseImage_->scale(factor);
			}
			double StickerHeight = StickerNode->image->height();
			unsigned Ycoord= StickerNode->y;
			double BaseHeight = BaseImage_->height();
			if(StickerHeight+Ycoord > BaseHeight){
				double Hfactor = (StickerHeight+Ycoord)/BaseHeight;
				BaseImage_->scale(Hfactor);
			}
			for(unsigned i=0;i<StickerNode->image->width();i++){
				for(unsigned j=0; j<StickerNode->image->height(); j++){
					HSLAPixel* StickerPixel = StickerNode->image->getPixel(i,j);
					if(StickerPixel->a != 0){
						HSLAPixel* BasePixel = BaseImage_->getPixel(Xcoord+i,Ycoord+j);
						BasePixel->h = StickerPixel->h;
						BasePixel->s = StickerPixel->s;
						BasePixel->l = StickerPixel->l;
						BasePixel->a = StickerPixel->a;
					}
				}
			}
			StickerNode=StickerNode->next;
		}
		return *BaseImage_;
	}
}
