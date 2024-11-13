import { Component, OnInit, Input, Output, EventEmitter } from "@angular/core";
import { clickListenerEvent } from "@patterns/common.model";
import { ProductcardModel } from "./productcard.model";
import { Observable } from "rxjs";
import { StringIdsType } from "src/stringIds";
import { TranslateService } from "@ngx-translate/core";
import { ImageSliderModel } from "@patterns/imageslider";

@Component({
  selector: 'pattern-productcard',
  templateUrl: './productcard.component.html',
  styleUrls: ['./productcard.component.css']
})
export class ProductcardComponent {
  @Input() public productcard: ProductcardModel;

  @Output() clickListener = new EventEmitter();

  imageSlider: ImageSliderModel;
  constructor(private translate: TranslateService) {}

  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }

  
  onClicked(event: Event) {
    const eventObject = new clickListenerEvent(event, this.productcard.id);
    if (this.productcard.event) {
      this.productcard.event(eventObject);
    } else {
      this.clickListener.emit(eventObject);
    }
  }
  round_the_value(value){
    return Math.round(100 * value) / 100
  }
}
