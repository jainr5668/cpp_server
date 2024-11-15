import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { ButtonModule } from '@patterns/button';
import { TableComponent } from './table.component';
import { ElementModule } from '@patterns/element';
@NgModule({
  declarations: [TableComponent, ],
  imports: [
    CommonModule,
    ButtonModule,
    ElementModule,
    ButtonModule
  ],
  exports: [TableComponent],
})
export class TableModule {}
