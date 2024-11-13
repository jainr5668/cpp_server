import { Component, Input, Output, EventEmitter } from "@angular/core";
import { TranslateService } from "@ngx-translate/core";
import { Observable } from "rxjs";
import { StringIdsType } from "src/stringIds";
import { CardModel } from "./card.model";

@Component({
  selector: 'pattern-card',
  templateUrl: './card.component.html',
  styleUrls: ['./card.component.css'],
})
export class CardComponent {
  @Input() public card: CardModel;

  @Output() clickListener = new EventEmitter();

  constructor(private translate: TranslateService) {
  }

  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }

  onClicked(event: Event) {
    if (this.card.event) {
      this.card.event(event);
    } else {
      this.clickListener.emit(event);
    }
  }
}
